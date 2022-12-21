//
// Created by alexw on 11/18/2022.
//

#ifndef GOLDFISH_LINKEDSTACK_H
#define GOLDFISH_LINKEDSTACK_H

#include "Stack.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;

template <typename T>
class LinkedStack : public Stack<T> {
private:

    struct Node {
        T value;
        Node* next;

        Node(T v = T(), Node* n = nullptr) : value(v), next(n) { }
    };

    Node *head, *last;

    void copy(const LinkedStack<T>&);

public:

    LinkedStack(); // constructor
    LinkedStack(const LinkedStack<T>&); // copy constructor
    LinkedStack<T>& operator=(const LinkedStack<T>&); // assignment overload
    virtual ~LinkedStack(); // destructor


    T peek() const override;
    void pop() override;
    void push(const T&) override;
    void rotate(typename Stack<T>::Direction) override;

    void clear() override;
    int getLength() const override;
    bool isEmpty() const override;

    template <typename U>
    friend ostream& operator<<(ostream&, const LinkedStack<U>&);
};



#include "LinkedStack.tpp"
#endif //GOLDFISH_LINKEDSTACK_H
