#include "ArrayStack.h"

int main() {
    ArrayStack stack;

    // One
    stack.operator<<(std::cout);
    std::cout << std::flush;

    //Two
    std::cout << stack << std::flush;

    return 0;
}
