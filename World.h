#ifndef __World_h__
#define __World_h__
#include "LinkedList.h"
#include "monitor.h"

#define INITIAL_SNAKE_LENGTH 3
#define MATRIX_LENGTH 32
#define MATRIX_WIDTH 16

struct Pixel {
    int x;
    int y;
    bool operator==(const Pixel&) const;
//    friend ostream& operator<<(ostream& os, const Pixel& p);
};

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum PLAYER {
    PLAYER1,
    PLAYER2
};

enum RESULT {
    PLAYING,
    PLAYER_1_WIN,
    PLAYER_2_WIN,
    TIE,
};

class Snake{
    private:
        LinkedList<Pixel> body;
        DIRECTION direction;
        friend class World;
    public:
        Snake();
        Snake(Pixel initialPoint, DIRECTION direction);
        bool move(bool forceGrow, Pixel food);
        bool isDead();
        void changeDirection(DIRECTION direction);
        Pixel getHead();
        void print();
        int size();
};

class World{
    private:
        Snake snake1;
        Snake snake2;
        Pixel food;
        int score1;
        int score2;
        RESULT result;
    public:
        World();
        void updateFood();
        void changeDirection(PLAYER player, DIRECTION direction);
        bool isGameOver();
        void update();
        void print();
        void draw();
};

#endif
