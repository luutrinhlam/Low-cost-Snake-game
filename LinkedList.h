#ifndef __LinkedList_h__
#define __LinkedList_h__

template <class T>
class LinkedList{
private:
    struct Node{
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;
    int size;
public:
    LinkedList();
    void add(T data);
    void print();
    void remove(int index);
    void insert(int index, T data);
    T get(int index);
    int getSize();
    void clear();
    bool find(T data);
};

#include "LinkedList.cpp"

#endif