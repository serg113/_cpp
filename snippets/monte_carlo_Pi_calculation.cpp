/*
    estimation of Pi by Monte Carlo method
    method -->
    suppose we have a circle with unit radius inscribed in a quadrant
    the ratio between randomly arranged points inside the circle and inside the quadrant (inside + outside the circle)
    approaches to Pi
    
    in example only 1/4 part of circle is taken 

*/

#include <iostream>
#include <stdlib.h>

int main()
{
    float x, y;
    int counter = 0;

    for(int i = 0; i < 10000; ++i)
    {
        x = (float)(rand()%100)/100;
        y = (float)(rand()%100)/100;

        if((x*x + y*y) <= 1)
            ++counter;
    }

    std::cout << (counter/10000.0)*4 << std::endl;

}
