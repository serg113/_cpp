// 'auto' keyword is used for type deduction at compile time
//
// for 'auto' return type compiler implements template type deduction 
// that ignores reference-ness of expression
// 
// 'decltype()' deduce the type of an expression
// 
// as an example of the two keywords usage the operator[] can be considered
// generally stl containers operator[] returns reference to 
// contained type so user can modify it
// 
// ref. --> page 26, "Effective Modern C++" by Scott Meyers


#include <iostream>
#include <vector>


template <typename C, typename Index>
auto f(const C& container, Index i)
{
    std::cout << "const reference and auto" << std::endl;
    return container[i];
}

template <typename C, typename Index>
decltype(auto) f(C& container, Index i)
{
    std::cout << "non const reference and decltype auto" << std::endl;
    return container[i];
}



int main()
{
    std::vector<int> v = {1, 2, 3, 4};
    
    f(v, 2) = 5;                                    // & + decltype(auto)
    
    std::cout << f(v, 2) << std::endl;              // & + decltype(auto)
    
    std::cout << f(std::move(v), 2) << std::endl;   // const & + auto
    
    // in the last expression it is assumed that temporary(move-ed) object 
    // will not be modified, so its lifetime will be extended only 

    return 0;
}
