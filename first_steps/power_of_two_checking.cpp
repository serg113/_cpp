/**
 * checking if number is power of 2
 */

#import <iostream>


bool binary_search(unsigned int a, int begin, int end)
{
    std::cout << "search between " << begin << " and " << end << std::endl;

    if(begin > end)
        return false;

    int middle = (end + begin)/2;

    if(a == (2 << middle))
        return true;

    if(a < (2 << middle)){
        return binary_search(a, begin, middle - 1);
    }
    else{
        return binary_search(a, middle + 1, end);
    }

}


int main()
{
    unsigned int a = 1073741823;
    std::cout << "search result for: " << a << " is " << ((binary_search(a, 0, 30) == true) ? "true" : "false") << std::endl;

    a = 2;
    std::cout << "search result for: " << a << " is " << ((binary_search(a, 0, 30) == true) ? "true" : "false") << std::endl;

    a = 5;
    std::cout << "search result for: " << a << " is " << ((binary_search(a, 0, 30) == true) ? "true" : "false") << std::endl;


    unsigned int b = 2 << 30; // max shift

    std::cout << "search result for: " << b << " is " << ((binary_search(b, 0, 30) == true) ? "true" : "false") << std::endl;
}
