
#include "LinkedQueue.h"

template <typename T>
LinkedQueue<T>::LinkedQueue()
: head(nullptr), last(nullptr) { }

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
T LinkedQueue<T>::back() const {
    if (isEmpty()) {
        throw string("back: error, queue is empty, cannot access the back");
    }

    return last->value;
}

template <typename T>
void LinkedQueue<T>::clear() {
    Node* prev = nullptr; // linear

    while (head != nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }

    last         = nullptr;
    this->length = 0;

    // alternative (but slightly less efficient, T(n) = 3n)
    
    // while (!isEmpty()) {
    //     dequeue();
    // }
}

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& copyObj) {
    this->length = copyObj.length; // linear
    head = last  = nullptr;

    if (this->length > 0) {
        head           = new Node(copyObj.head->value);
        Node* myCurr   = head;
        Node* copyCurr = copyObj.head->next;

        while (copyCurr != nullptr) {
            Node* n      = new Node(copyCurr->value);
            myCurr->next = n;
            myCurr       = n;
            copyCurr     = copyCurr->next;
        }

        last = myCurr;
    }
}

template <typename T> // constant
void LinkedQueue<T>::dequeue() { // remove front
    if (isEmpty()) {
        throw string("dequeue: error, stack is empty, cannot remove front");
    }

    Node* prev = head;
    head       = head->next;
    delete prev;
    this->length--;

    if (head == nullptr) {
        last = nullptr;
    }
}

template <typename T> // constant
void LinkedQueue<T>::enqueue(const T& elem) { // append
    Node* n = new Node(elem);

    if (isEmpty()) {
        head = last = n;
    }
    else {
        last->next = n;
        last       = n;
    }

    this->length++;
}

template <typename T> // constant
T LinkedQueue<T>::front() const { // return front elem
    if (isEmpty()) {
        throw string("front: error, queue is empty, cannot access the front");
    }

    return head->value;
}

template <typename T>
int LinkedQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return this->length == 0;
}

template<typename U>
ostream &operator<<(ostream& outStream, const LinkedQueue<U>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "Queue is empty, no elements to display.\n";
    }
    else {
        typename LinkedQueue<U>::Node* curr = myObj.head; // head is the front of the queue
//        outStream << "[H] ";
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
//                outStream << ", ";
                outStream << endl;

            }
            curr = curr->next;
        }
//        outStream << endl;
    }

    return outStream;
}


