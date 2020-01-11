// this code checks if integer is power of 2

bool check(int n)
{
  if(n > 0 && (n & (n-1) == 0))
    return true;
  return false;
}
  
