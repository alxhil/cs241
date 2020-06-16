#include <stdio.h>

int factorial(int n)
{
  int result = 1;
  while(n--)
  {
    result *= n;
  }
  return result;
}

int main(void)
{
  int n = 5;
  int fact = factorial(5);
  printf("%d! = %d\n", n, fact);
  return 0;
}
