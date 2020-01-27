/*
* Fibonacci numbers are calculated as F(n) = F(n-1) + F(n-2)
* with condition, that F(0) = 0 and F(1) = 1
* but interesting case is with memoization - dynamic programming
* memoization optimizes Fibonacci numbers calculation in the case when we have range of numbers
*/

#include <iostream>
#include <unordered_map>

std::unordered_map<int, int> memo = {{0,0},{1,1}};

int fib(int);

int main()
{
    for(int i = 0; i <= 10; ++i)
    {
        std::cout << "fib(" << i << ") = " << fib(i) << std::endl;
    }
}

int fib(int n)
{
    auto search_res = memo.find(n);

    if(search_res != memo.end())
    {
        return search_res -> second;
    }
    else
    {
        int res = fib(n - 1) + fib(n - 2);

        memo.emplace(std::make_pair(n, res));

        return res;
    }
}
