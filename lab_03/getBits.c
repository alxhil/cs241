/*Alex Hill */
/*  2/11/18 */
/*Section 05*/
#include <stdlib.h> /*USED FOR EXIT(); it is very similar to break in java*/
#include <stdio.h>
#define IN 1 /*True*/
#define OUT 0 /*False*/
int xBig; /*Big x value that I don't want to type in every time I need this number(~4.3 Billion)*/
unsigned long readUL(void); /*Reads in lines*/
unsigned int getbits(unsigned int x, int p, int n);
int main (void)
{
  unsigned int x; /*wrote these again b/c unsigned int is outside function*/
  int p; /*same as above*/
  int n; /*same as above*/
  while (IN)
    {        
      xBig = OUT; /*Reads in lines, much easier to use than I thought*/       
      x = readUL();         
      p = (int) readUL(); /*needs an int cast*/
      n = (int) readUL(); /*needs an int cast*/
      /*ALL IN ORDER WHEN READING IN NUMBERS*/
      /*Watches for x value being too big*/        
      if (xBig)
	{             
	  printf("Error: value out of range\n");
	}
      /*Watches for p value being too big*/        
      else if (p > 31)
	{
	  printf("Error: position out of range\n");
	}
      /*Watches for n value being too big*/        
      else if (n > 31) /*Watches for n value being too big compared to p*/  
	{
	  printf("Error: number of bits out of range\n");
	}       
      else if (n > (p+1))
	{
	  printf("Error: too many bits requested from position\n");
	}
      /*If everything passes, print line*/
      else
	{
	  printf("getbits(x=%u, p=%d, n=%d) = %u\n",x ,p, n, getbits(x, p, n));
	}
    }
  return 0;
}


/*while ((getnum = gtechar()) != EOF)*/
unsigned long readUL(void)
{  
  /*can handle more bits than float (could be overkill but oh well*/ 
  double number = 0;
  char c;
  int searchDone = OUT;/*knows when to stop searching*/
  while (searchDone != IN)
    {        
      c = getchar();       
      if (c == EOF)
	{
	  exit(0); /*ends program if EOF*/
	}
      else if (c >= '0' && c <= '9') 
	{             
	  number *= 10; /*have both of these since number is a double*/        
	  number += c - '0';
	  /*0xffffffff is the largest value possible for computers*/
	  /*At least on the linux machines or my own*/               
	  if (number > 0xffffffff) 
	    {
	      xBig = IN;
	    }
	}        
      else searchDone = IN;
    }   
  return number;
}
/*Math to give the answer for each line + given in book*/
unsigned int getbits(unsigned x, int p, int n)
{    
  return (x >> (p+1-n)) & ~(~0 << n);
  /*algorithm is from pg 49 in book It is extremely useful*/
}                                                                  
