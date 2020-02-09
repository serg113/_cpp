/**
 * about function reference qualifier syntax
 * available in C++11
 *
 */

#include <iostream>

class Test
{
public:
    void print() &
    {
        std::cout << "call from lvalue object" << std::endl;
    }
    void print() &&
    {
        std::cout << "call from rvalue object" << std::endl;
    }
};

int main()
{
    Test t;
    t.print();      // calls print() &

    Test().print(); // calls print() &&
}

