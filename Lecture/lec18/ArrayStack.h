#include <iostream>

class ArrayStack {
public:
    ArrayStack();
    ~ArrayStack();
    void push(int n);
    int peek();
    int pop();
    bool isEmpty() const;
    std::ostream& operator <<(std::ostream& out);
    friend std::ostream& operator<<(std::ostream& out, const ArrayStack& stack);     // should extra permission to private variables
private:
    ArrayStack(const ArrayStack& other);
    int *elements;
    int size;
    int capacity; // cannot initialize here in c++
};
