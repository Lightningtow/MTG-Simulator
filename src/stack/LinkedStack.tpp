//
// Created by alexw on 11/18/2022.
//

//#include "LinkedStack.h"


template<typename T>
void LinkedStack<T>::copy(const LinkedStack<T>& obj) {
    this->length = obj.length;
    head = last  = nullptr;

    if (this->length > 0) {
        head = new Node(obj.head->value);
        Node* curr = head;
        Node* copyCurr = obj.head->next;

        while (copyCurr != nullptr) {
            Node* n = new Node(copyCurr->value);
            curr->next = n;
            curr = n;
            copyCurr = copyCurr->next;
        }

        last = curr;
    }
}

template<typename T>
LinkedStack<T>::LinkedStack() {
    head = nullptr;
    last = nullptr;
}

template<typename T> // copy constructor
LinkedStack<T>::LinkedStack(const LinkedStack<T>& obj) {
    copy(obj);
}

template<typename T> // assignment operator
LinkedStack<T> &LinkedStack<T>::operator=(const LinkedStack<T>& obj) {
    if (this != &obj) {
        clear();
        copy(obj);
    }
    return *this;
}

template<typename T> // destructor
LinkedStack<T>::~LinkedStack() {
   clear();
}

template<typename T>
void LinkedStack<T>::clear() {
    while(!this->isEmpty()) {
        pop();
    }
}

template<typename T>
int LinkedStack<T>::getLength() const {
    return this->length;
}

template<typename T>
bool LinkedStack<T>::isEmpty() const {
    if(this->length == 0) return true;
    else return false;
}

template<typename T>
T LinkedStack<T>::peek() const {
    if(this->isEmpty()) {
        string e = "error in peek(): stack is empty";
        cout << e << endl;
        throw(e);
    }
    else return head->value;
}

template<typename T>
void LinkedStack<T>::pop() {
    if(this->isEmpty()) {
        string e = "error in pop(): stack is empty";
        cout << e << endl;
        throw(e);
    }

    Node* prev = head;
    head = head->next;
    delete prev;
    this->length--;

    if(head == nullptr) {
        last = nullptr;
    }
}

template<typename T>
void LinkedStack<T>::push(const T& elem) {
    Node* newnode = new Node(elem);

    if (this->isEmpty()) {
        head = last = newnode;
    }
    else {
        newnode->next = head;
        head = newnode;
    }

    this->length++;
}



// error: O(1)
// rotate right: O(1)
// rotate left: O(n)
template<typename T>
void LinkedStack<T>::rotate(typename Stack<T>::Direction dir) {
    if (this->isEmpty()) {
        string e = "error in rotate(): stack is empty";
        cout << e << endl;
        throw(e);
    }
    else if (dir == Stack<T>::RIGHT) { // top elem to bottom
        T mover = peek();
        Node* newnode = new Node(mover);

        last->next = newnode;
        last = newnode;

        pop();
        this->length++; // to cancel out the reduction from pop()
    }

    else if (dir == Stack<T>::LEFT) { // bottom elem to top
        T bottom = last->value;
        push(bottom); //move bottom element to top
        this->length--; // to cancel out the addition from push()


        Node* curr = head;
        while(curr->next != last) { // traverse until curr is second to last
            curr = curr->next;
        }

        delete curr->next; //delete last element in stack
        curr->next = nullptr;
        last = curr; // change `last` pointer to the actual last element


    }
    else {
        string e = "error in rotate(): invalid direction";
        cout << e << endl;
        throw(e);
    }
}


template <typename T>
ostream& operator<<(ostream& outStream, const LinkedStack<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename LinkedStack<T>::Node* curr = myObj.head; // head is the top of the stack
//        outStream << "[H] ";
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << ", ";
//                outStream << endl;

            }
            curr = curr->next;
        }
//        outStream << endl;
    }

    return outStream;
}