#include "ArrayStack.h"

ArrayStack::ArrayStack() {
    size = 0;
    capacity = 10;
    elements = new int[capacity]();
}
ArrayStack::~ArrayStack() {
    delete[] elements;
}
void ArrayStack::push(int n) {
    if (size >= capacity) {
        int *bigger = new int[capacity * 10];
        for (int i = 0; i < size; i++) {
            bigger[i] = elements[i];
        }
        delete[] elements;
        elements = bigger;
        capacity *= 10;
    }
    elements[size] = n;
    size++;
}
int ArrayStack::peek() {
    if (isEmpty()) throw "empty!!";
    return elements[size - 1];
}
int ArrayStack::pop() {
    int result = peek();
    elements[size - 1] = 0;
    size--;
    return result;
}
bool ArrayStack::isEmpty() const {
    return size == 0;
}
std::ostream& ArrayStack::operator <<(std::ostream& out) {
    out << "{";
    if (!isEmpty()) {
        out << elements[0];
        for (int i = 1; i < size; i++) {
            out << ", " << elements[i];
        }
    }
    out << "}";
    return out;
}

std::ostream& operator<<(std::ostream& out, const ArrayStack& stack){
    out << "{";
    if (!stack.isEmpty()) {
        out << stack.elements[0];
        for (int i = 1; i < stack.size; i++) {
            out << ", " << stack.elements[i];
        }
    }
    out << "}";
    return out;
}
