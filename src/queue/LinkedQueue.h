#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "Queue.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue : public Queue<T> {
    protected:
        // represents an element in the queue
        struct Node {
            T value;
            Node* next;

            Node(T v = T(), Node* n = nullptr)
            : value(v), next(n) { }
        };

        // a pointer to the front (head) and back (last) of the queue
        Node *head, *last;

    private:
        // copy the state of the argument queue to `this`
        void copy(const LinkedQueue<T>&);

    public:
        // default constructor
        LinkedQueue();

        // copy constructor
        LinkedQueue(const LinkedQueue<T>&);

        // overloaded assignment operator
        LinkedQueue<T>& operator=(const LinkedQueue<T>&);

        // destructor
        virtual ~LinkedQueue();




        // add the argument to the back of the queue
        virtual void enqueue(const T&) override; // constant time complexity

        // return the element at the back of the queue
        virtual T back() const override;

        // return the element at the front of the queue
        virtual T front() const override;

        // remove the front element from the queue
        virtual void dequeue() override;




        // remove all elements in the queue, resetting to the initial state
        virtual void clear() override;

        // return the current length of the queue
        virtual int getLength() const override;

        // determine if the queue currently empty
        virtual bool isEmpty() const override;

        template <typename U>
        friend ostream& operator<<(ostream&, const LinkedQueue<U>&);


};

#include "LinkedQueue.tpp"
#endif
