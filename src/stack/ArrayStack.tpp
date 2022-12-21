

#include "ArrayStack.h"
using namespace std;

// I won't insult you by telling you what it means to push and pop a stack :P
//      so I'll document just the time complexities


template <typename T> // constant
int ArrayStack<T>::getLength() const {
    return this->length;
}

template <typename T> // constant
int ArrayStack<T>::getMaxSize() const {
    return maxSize;
}

template <typename T> // constant
bool ArrayStack<T>::isEmpty() const {
    return (this->length == 0);
}

template <typename T> // constant
bool ArrayStack<T>::isFull() const {
    return (this->length == maxSize);
}

template <typename T> // constant
T ArrayStack<T>::peek() const {
    if (isEmpty()) {
        throw string("error in ArrayStack::peek(): empty stack");
    }

    return buffer[this->length - 1];
}

template <typename T> // constant
void ArrayStack<T>::pop() {
    if (isEmpty()) {
        throw string("error in ArrayStack::pop(): empty stack");
    }

    this->length--;
}

template <typename T> // constant
void ArrayStack<T>::push(const T& elem) {
    if (isFull()) {
        throw string("error in ArrayStack::peek(): stack is full");
    }

    if (buffer == nullptr) {
        buffer = new T[maxSize];
    }

    buffer[this->length++] = elem;
}


template <typename T> // constant
ArrayStack<T>::ArrayStack(int i)
: buffer(new T[i]), maxSize(i) { }

template <typename T> // linear
ArrayStack<T>::ArrayStack(const ArrayStack<T>& copyObj) {
    copy(copyObj);
}

template <typename T> // linear
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T> // constant
ArrayStack<T>::~ArrayStack() {
    clear();
}

template <typename T> // constant since (I belive) deleting an entire array in one shot doesn't care about the amount of elements,
void ArrayStack<T>::clear() {   // but it could be linear, depending if you're counting "how many times does each line of code execute"
    delete[] buffer;            // or "how many things are done behind the scenes"
    buffer = nullptr;
    this->length = 0;
}

template <typename T> // linear
void ArrayStack<T>::copy(const ArrayStack<T>& copyObj) {
    this->clear();
    this->length = copyObj.length;
    maxSize = copyObj.maxSize;
    buffer = new T[maxSize];

    copyRec(copyObj, 0);


//    for (int i = 0; i < copyObj.length; i++) {
//        buffer[i] = copyObj.buffer[i];
//    }
}


template <typename T> // linear
void ArrayStack<T>::rotate(typename Stack<T>::Direction dir) {
/* I split the rotateRec into two separate functions, because it seemed better than the alternative
 *      of passing 'left' or 'right' as an argument each time and having a conditional within every statement
 *
 */

    if (isEmpty()) {
        throw string("rotate: error, stack is empty, unable to rotate");
    }
    else if (dir == Stack<T>::RIGHT) { // top elem to bottom
        T top = peek();

        rotateRecRight(this->length-2);

        buffer[0] = top; // I would put this in the base case `if` for rotateRecRight but I don't know how to give it access to `top`
        // except by passing it as a parameter every single time and that just needlessly wastes execution time
    }
    else if (dir == Stack<T>::LEFT) { // bottom elem to top

        T bottom = buffer[0];

        rotateRecLeft(1);

        buffer[this->length - 1] = bottom; // same deal as above, can't easily put this in the recursive base case

    }
    else {
        throw string("rotate: error, unknown direction");
    }



//   right \/
//        for (int i = this->length - 2; i >= 0; i--) { // top is highest array index
//            buffer[i + 1] = buffer[i]; // so move everything upwards
//        } // and then put the top elem on the bottom



//     left \/
//        for (int i = 1; i < this->length; i++) {
//            buffer[i - 1] = buffer[i];
//        }


}

template<typename T> // linear overall (when including all instances of recursion)
unsigned ArrayStack<T>::rotateRecRight(unsigned int i) { // top elem to bottom

    if(i == -1) return 0; // base case

    buffer[i + 1] = buffer[i]; // shift elem upwards

    return rotateRecRight(i-1); // recursion

}


template<typename T> // linear overall (when including all instances of recursion)
unsigned ArrayStack<T>::rotateRecLeft(unsigned int i) { // bottom elem to top
    if(i >= this->length) return 0; // base case

    buffer[i - 1] = buffer[i]; // shift elem downwards

    return rotateRecLeft(i+1); // recursion

}


template<typename T> // linear overall (when including all instances of recursion)
unsigned ArrayStack<T>::copyRec(const ArrayStack<T>& copyObj, unsigned i) {
    if(i == this->length) return 0; // base case

    buffer[i] = copyObj.buffer[i]; // copy

    return copyRec(copyObj, i+1); // make it recursive

}
