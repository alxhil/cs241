/*Name: Alex Hill        */
/*CS-241-005             */
/* March 3rd 2018        */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* used to compare strings in main method*/
void d2b(int d);
void b2d(int d);
int main(int argc, char* argv[])
{
  long num = strtol(argv[2], NULL, 10);
  char* binary = "-b2d";
  char* decimal = "-d2b";
  if((argc = 3))
    {
      if(strcmp(argv[1],decimal))
	{
	  d2b(num);
	}
      else if(strcmp(argv[1],binary))
	{
	  b2d(num);
	}
      else
	{
	  printf("Error");
	}
      
    }
  return 0;
}
/*Decimal to binary */
void d2b (int d)
{
  int remainder;
  int binary = 0;
  int base = 1;
  if(d > 255)
    {
      printf("Error \n");
      exit(0);
    }
   /*To find binary from decimal we divide by 2 until we can't anymore*/
  while (d > 0)
    {
      remainder = d % 2;
      binary = binary + remainder * base;
      d = d / 2;
      base = base * 10;
    }
  
  printf("%d\n", binary);
  /* source: https://codingcompiler.com/c-program-to-convert-decimal-to-binary/ */
}
/*Binary to decimal */
void b2d (int d)
{
  int decimal = 0;
  int base = 1;
  int remainder = 0;
  if(d > 1111111111111111)
    {
      printf("Error");
      exit(0);
    }
  while (d > 0)
    {
      remainder = d % 10;
      decimal = decimal + remainder * base;
      d = d / 10 ;
      base = base * 2;
    }
     printf("%d \n",decimal);
  /* source: http://www.sanfoundry.com/c-program-binary-number-into-decimal/ */	
}
      
