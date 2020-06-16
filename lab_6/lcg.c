/* Alex Hill */
/* CS 241L-005 */
/* March-22-2018 */
#include<stdio.h>
#include "lcg.h"
long primeTest(unsigned long n)
{
  unsigned long div = 2;
  unsigned long num = 1;
  while (div <= n)
    {
      if (n % div == 0)
	{
	  num *= div;
	  while (n % div == 0)
	    {
	      n /= div;
	    }
	}
      div++;
    }
  return num;
}
struct LinearCongruentialGenerator makeLCG(unsigned long m, unsigned long c)
{
  struct LinearCongruentialGenerator lcg2;
  unsigned long p = primeTest(m);
  if (m % 4 == 0)
    {
      lcg2.a = 1+2*p;
    }
  else
    {
      lcg2.a = 1+p;
    }
  if (lcg2.a > m || m < 0 || lcg2.a < 0 || c < 0 || c > m)
    {
      lcg2.a = lcg2.c = lcg2.m = lcg2.x = 0;
    }
  else
    {
      lcg2.c = c;
      lcg2.x = c;
      lcg2.m = m;
    }
  return lcg2;
}
unsigned long getNextRandomValue(struct LinearCongruentialGenerator* lcg)
{
  unsigned long next;
  next = lcg -> x;
  lcg -> x = ((lcg -> a* lcg -> x + lcg -> c) %lcg -> m);
  return next;
}










