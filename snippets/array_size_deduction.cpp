/*
 * the compiler can deduce the size of an array passed by reference
 *
 * so the call get_size(arr) is the same as get_size(const char (&)[13])
 *
 * the last expression make it obvious that
 * get_size() function accepts not only reference to array
 * but also it's size
 *
 *  *  *  *  *  *  *
 * ref. --> page 16 - "Effective Modern C++" by Scott Meyers
 */

#include <iostream>

template <typename T, std::size_t N>
std::size_t get_size(T(&arr)[N])
{
    std::cout << arr << std::endl;
    return N;
}

int main()
{
    const char arr[] = {"hello array!"};

    std::size_t sz = get_size(arr);

    std::cout << "size of array is: " << sz << std::endl;
}


