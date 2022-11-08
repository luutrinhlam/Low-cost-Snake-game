#include <iostream>
#include "LinkedList.h"

using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <class T>
void LinkedList<T>::add(T data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = tail->next;
    }
    size++;
}

template <class T>
void LinkedList<T>::print()
{
    cout << "Size: " << size << endl;
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <class T>
void LinkedList<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        cout << "Index out of range" << endl;
        return;
    }
    if (index == 0)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        Node *temp2 = temp->next;
        temp->next = temp2->next;
        delete temp2;
    }
    size--;
}

template <class T>
void LinkedList<T>::insert(int index, T data)
{
    if (index < 0 || index > size)
    {
        cout << "Index out of range" << endl;
        return;
    }
    if (index == 0)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node *temp = head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = temp->next;
        temp->next = newNode;
    }
    size++;
}

template <class T>
T LinkedList<T>::get(int index)
{
    if (index < 0 || index >= size)
    {
        cout << "Index out of range" << endl;
        T t;
        return t;
    }
    Node *temp = head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp->data;
}

template <class T>
int LinkedList<T>::getSize()
{
    return size;
}

template <class T>
void LinkedList<T>::clear()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        Node *temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
}

template <class T>
bool LinkedList<T>::find(T data)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == data)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}