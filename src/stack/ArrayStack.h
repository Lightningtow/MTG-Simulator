#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "Stack.h"
#include <iostream>
using namespace std;

template <typename T>
class ArrayStack : public Stack<T> {
    private:
        // an array that contains the elements
        T* buffer;

        // the maximum number of elements in the stack
        int maxSize;

        // copy the state of the argument stack to `this`
        void copy(const ArrayStack<T>&);

        unsigned copyRec(const ArrayStack<T>&, unsigned);

        unsigned rotateRecLeft(unsigned);  // it's much better performance to split them into two functions
        unsigned rotateRecRight(unsigned); // than to pass direction as an argument and then check for it 60*42 times

    public:
        // constructor with the maximum size as the argument
        ArrayStack(int = 100);

        // copy constructor
        ArrayStack(const ArrayStack<T>&);

        // overloaded assignment operator
        ArrayStack<T>& operator=(const ArrayStack<T>&);

        // destructor
        virtual ~ArrayStack();

        // remove all elements in the stack, resetting to the initial state
        void clear() override;

        // return the current length of the stack
        int getLength() const override;

        // return the maximum size of the stack
        int getMaxSize() const;

        // determine if the stack currently empty
        bool isEmpty() const override;

        // determine if the stack is currently full
        bool isFull() const;

        // return the element at the top of the stack
        T peek() const override;

        // remove the top element from the stack
        void pop() override;

        // add the argument to the top of the stack
        void push(const T&) override;

        // rearranges the elements in the stack according to the argument
        void rotate(typename Stack<T>::Direction) override;



};

#include "ArrayStack.tpp"
#endif
