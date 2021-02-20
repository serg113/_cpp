/*
	Euclid's algorithm to find greatest common divisor of two numbers
  
  Can be found at first pages of book R. Sedgewick "Algorithms"

  Assumptions: 
    1. a, b are integers
    2. a > b > 0
    
  Find c
    that 
      a mod c = 0 
      and 
      b mod c = 0
      
	Algorithm:
		assume we have sequence of numbers
			a > b > R1 > R2 > R3 > ... > Rn
		where Rk is reminder of R(k-2)/R(k-1) and R(n-1)/Rn has no reminder
    so in this sequence Rn is the GCD

		that is
			a  = b*m0  + R1
			b  = R1*m1 + R2
			R1 = R2*m2 + R3
			...
			R(n-1) = Rn*mn

		the existence of Rk sequence can be approved by induction

	In sum we need to calculate modulo of two sequential numbers until it becomes zero.


*/

#include <iostream>

int calculate_gcd(int a, int b)
{
	if(a < b) 
		return calculate_gcd(b, a);
	
	int k = a % b;

	if(k == 0) 
		return b;
	else 
		return calculate_gcd(b, k);
}

int main()
{
	int a;
  std::cin >> a;
  
  int b;
  std::cin >> b;
	
	std::cout << std::endl;	
	std::cout << "gcd(" << a << ", " << b << ") = " << calculate_gcd(a, b) << std::endl;
}
