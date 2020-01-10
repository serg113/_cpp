//check if number is multiple of 4

// output -> 4 8 12

#include <iostream>

int main()
{
  for(int i = 1; i <=15; ++i) {
    if(0 == (i & 3)) {
      std::cout << i << std::endl; 
  }
}
