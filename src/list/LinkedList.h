#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "List.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList : public List<T> {
    protected:
        // represents an element in the linked list
        struct Node {
            T value;
            Node* next;

            Node(T v = T(), Node* n = nullptr)
            : value(v), next(n) { }
        };

        // a pointer to the front of the list
        Node* head;

    private:
        // copy the state of the argument list to `this`
        void copy(const LinkedList<T>&);

    public:
        // default constructor
        LinkedList();

        // copy constructor
        LinkedList(const LinkedList<T>&);

        // overloaded assignment operator
        LinkedList<T>& operator=(const LinkedList<T>&);

        // destructor
        virtual ~LinkedList();

        // add the argument to the end of the list
        void append(const T&) override;

        // remove all elements in the list, resetting to the initial state
        void clear() override;

        // return the element at the given position (argument)
        T getElement(int) const override;

        // return the current length of the list
        int getLength() const override;

        // insert the given element (argument 2) at
        // the given position (argument 1)
        void insert(int, const T&) override;

        // determine if the list currently empty
        bool isEmpty() const override;

        // remove the element at the given position (argument)
        void remove(int) override;

//        void removeCard(Card); // want to make it a clearly separate function and not just overload the remove()
        // because this only works with Cards

        // replace the element at the given position (argument 1) with
        // the value given (argument 2)
        void replace(int, const T&) override;

        // overloaded stream insertion operator to make printing easier
        template <typename U>
        friend ostream& operator<<(ostream&, const LinkedList<U>&);

        void listToVector(vector<T> &vec);
};

#include "LinkedList.tpp"
#endif
