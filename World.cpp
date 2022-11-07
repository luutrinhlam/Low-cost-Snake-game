#include "World.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

bool Pixel::operator==(const Pixel &p) const
{
    return x == p.x && y == p.y;
}

Snake::Snake(){}

Snake::Snake(Pixel initialPoint, DIRECTION direction)
{
    /// @brief  Constructor of Snake class
    /// @param initialPoint The initial tail of the snake
    /// @param direction The direction heading of the snake
    body.add(initialPoint);
    this->direction = direction;

    // Add the rest of the initial body
    for (int i = 0; i++; i < INITIAL_SNAKE_LENGTH)
    {
        this->move(true, Pixel{-1, -1});
    }
}

bool Snake::move(bool forceGrow = false, Pixel food = {0, 0})
{
    /// @brief  Move the snake
    /// @param forceGrow If true, the snake will grow by 1
    /// @param food The food to check if the snake ate it
    Pixel head = getHead();
    Pixel newHead = head;
    switch (direction)
    {
    case UP:
        newHead.y--;
        break;
    case DOWN:
        newHead.y++;
        break;
    case LEFT:
        newHead.x--;
        break;
    case RIGHT:
        newHead.x++;
        break;
    }

    // Check if the snake ate the food
    bool ateFood = newHead == food;

    // Move the snake
    body.insert(0, newHead);
    if (!forceGrow && !ateFood)
    {
        body.remove(body.getSize() - 1);
    }

    return ateFood;
}

bool Snake::isDead()
{
    /// @brief  Checks if the snake is dead
    /// @return True if the snake is dead, false otherwise

    // Check if the snake is out of bounds
    Pixel head = getHead();
    if (head.x < 0 || head.x >= MATRIX_LENGTH || head.y < 0 || head.y >= MATRIX_WIDTH)
    {
        return true;
    }

    // Check if the snake is eating itself
    body.remove(0);
    bool isDead = body.find(head);
    body.insert(0, head);
    return isDead;
}

void Snake::changeDirection(DIRECTION direction)
{
    /// @brief  Changes the direction of the snake
    /// @param direction The new direction of the snake
    this->direction = direction;
}

Pixel Snake::getHead()
{
    /// @brief  Returns the head of the snake
    /// @return The head of the snake
    return body.get(0);
}

World::World()
{
    /// @brief  Constructor of World class
    srand(time(NULL));
    Pixel initialPoint;
    initialPoint.x = MATRIX_LENGTH / 2;
    initialPoint.y = MATRIX_WIDTH / 2;
    snake1 = Snake(initialPoint, RIGHT);
    snake2 = Snake(initialPoint, LEFT);
    score1 = 0;
    score2 = 0;
    result = PLAYING;
    updateFood();
}

void World::updateFood()
{
    /// @brief  Updates the position of the food
    Pixel newFood;
    newFood.x = rand() % MATRIX_LENGTH;
    newFood.y = rand() % MATRIX_WIDTH;
    food = newFood;
}

void World::changeDirection(PLAYER player, DIRECTION direction)
{
    /// @brief  Changes the direction of the snake
    /// @param player The player who wants to change the direction
    /// @param direction The new direction of the snake
    if (player == PLAYER1)
    {
        snake1.changeDirection(direction);
    }
    else
    {
        snake2.changeDirection(direction);
    }
}

bool World::isGameOver()
{
    /// @brief  Checks if the game is over
    /// @return True if the game is over, false otherwise
    if (snake1.isDead() && snake2.isDead())
    {
        result = TIE;
    }
    else if (snake1.isDead() || snake2.body.find(snake1.getHead()))
    {
        result = PLAYER_2_WIN;
    }
    else if (snake2.isDead() || snake1.body.find(snake2.getHead()))
    {
        result = PLAYER_1_WIN;
    }
    else
    {
        result = PLAYING;
        return false;
    }
    return true;
}

void World::update()
{
    /// @brief  Updates the world
    if (result == PLAYING)
    {
        bool ateFood1 = snake1.move(false, food);
        bool ateFood2 = snake2.move(false, food);
        if (ateFood1 || ateFood2)
        {
            updateFood();
        }
        if (ateFood1)
        {
            score1++;
        }
        if (ateFood2)
        {
            score2++;
        }
        if (isGameOver())
        {
            switch (result)
            {
                {
                case PLAYER_1_WIN:
                    score1 += 3;
                    break;
                case PLAYER_2_WIN:
                    score2 += 3;
                    break;
                default:
                    break;
                }
                cout << "Result: " << result << endl;
            }
        }
    }
}

void Snake::print()
{
    /// @brief  Prints the snake
    body.print();
    cout << "Direction: " << direction << endl;
}

void World::print(){
    /// @brief  Prints the world
    cout << "Score 1: " << score1 << endl;
    cout << "Score 2: " << score2 << endl;
    cout << "Result: " << result << endl;
    cout << "Snake 1: " << endl;
    snake1.print();
    cout << "Snake 2: " << endl;
    snake2.print();
    cout << "Food: " << food.x << ", " << food.y << endl;
}
