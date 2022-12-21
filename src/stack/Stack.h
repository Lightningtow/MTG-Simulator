#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
    public:
        enum Direction {
            RIGHT, LEFT,
        };

    protected:
        // the current number of elements in the stack
        int length;

    public:
        // default constructor
        Stack() : length(0) { }

        // destructor
        virtual ~Stack() { }

        // remove all elements in the stack, resetting to the initial state
        virtual void clear() = 0;

        // return the current length of the stack
        virtual int getLength() const = 0;

        // determine if the stack is currently empty
        virtual bool isEmpty() const = 0;

        // return the element at the top of the stack
        virtual T peek() const = 0;

        // remove the top element from the stack
        virtual void pop() = 0;

        // add the argument to the top of the stack
        virtual void push(const T&) = 0;

        // rearranges the elements in the stack according to the argument
        virtual void rotate(Direction) = 0;
};

#endif
