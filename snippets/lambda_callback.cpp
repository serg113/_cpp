#include <iostream>

void evaluate(void(*fn)(int), int n)
{
  fn(n);
}

int main(){

  void(*print)(int) = [](int n){std::cout << n << std::endl;};
  
  evaluate(print, 5);
}
