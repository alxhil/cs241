/* Alex Hill */
/* CS-241-005 */
/* Cipher Lab */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lcg.h"
#include <math.h>

int specialError;
int firstRandom;
int decrypt;
int encrypt;
int error;
int eof;
int numLines;
int genLCG;

struct LinearCongruentialGenerator Lcg;

unsigned long key;
unsigned long m;
unsigned long c;
/*Helper method skipLine, it skips to the end of a given line in case there is an error so there is not overlapping issues */
int skipLine()
{
  char c;
  c = getchar();
  while(c != EOF || c != '\n')
    {
      if(c == EOF)
	      {
	        return 10;
	      }
      if(c == '\n')
	      {
	        return 9;
        }
      c = getchar();
    }
  return 0;
}
/*Helper method getMode, it finds the first character of a line so that it can determine if its going to use encryption, decryption, or if its an error */
void getMode() {
  char c = getchar();
  if(c == 'e')
    {
      encrypt++;
    }
  else if(c == 'd')
    {
      decrypt++;
    }
  else if(c == '\n')
    {
      numLines++;
    }
  else if(c == EOF)
    {
      eof++;
    }
  else
    {
      error++;
    }
}
/*Another helper method, it sets an array  20 size to null terminators so it can be converted to unsigned longs later */
/*Then it reads in the M and C that will be used in the readLCGs method later */
unsigned long getLCGs()
{
  char c;
  int i;
  int l = 0;
  char lcg_m [21];
  unsigned long num;
  for(i = 0; i < 21; i++)
    {
      lcg_m[i] = '\0'; /* This is to be able to strtoul later */
    }
  c = getchar();
  if(c == ',')
    {
      return 0;
    }
  while(c != ',')
    {
      if(c>='0' && c<='9') /*error checking*/
	      {
	        lcg_m[l] = c;
	        l++;
	      }
      else
	      {
	        return 0;
	      }
      c = getchar(); /* This is to get another character or else it will just stay the same */
    }
  if(l > 21)
    {
      return 0;
    }
  num = strtoul(lcg_m, NULL, 10);
  return num;
}
/*helper method readLCGs, it takes the M and C values from getLCGs method and uses it to make an LCG which is then used to make a random value */
unsigned long readLCGs()
{
  unsigned long m_e;
  unsigned long c_e;
  if(genLCG == 1)
    {
      m_e = getLCGs();
      c_e = getLCGs();
      if(m_e == 0 || c_e == 0)
	      {
	        if(skipLine() == 9)
	          {
	            printf("Error");
	            return 555;
	          }
	        return 0;
	      }
  Lcg = makeLCG(m_e,c_e);
  genLCG--;
  }
  if(Lcg.a == 0  || Lcg.m == 0)
    {
      if(skipLine() == 9)
	      {
	        printf("Error\n");
	        specialError++;
	        return 555;
        }
      else
	      {
	        specialError++;
	        return 555;
	      }
    }
  key = getNextRandomValue(&Lcg);
  return key;
}

/*Encryption */
/*uses helper method readLCGs to find the nextRandomValue after some error checking it will encrypt the byte using */
/*the algorithm (char byte)^(randomValue%128) */
int encryption()
{
  char c;
  char eC;
  char temp;
  int firstDone;
  unsigned long randomVal;
  if(firstRandom == 1)
    {
      randomVal = readLCGs();
      if(randomVal == 555)
	      {
	        return 0;
	      }
      firstDone = 0;
      firstRandom--;
    }
  c = getchar();
  while(c!='\n' || c!=EOF)
    {
      if(c == '\n' || c ==EOF)
	      {
	        return 0;
	      }
      if(firstDone >= 1)
	      {
	        randomVal = readLCGs();
	        if(randomVal == 555)
	          {
	            if(skipLine() == 9)
		            {
		              return 0;
		            }
	            else
		            {
		              return 0;
		            }
	            }
	          }
          firstDone++;
          eC = c^(randomVal%128);
          if(eC < 32)
	          {
	            temp = ('?' + eC);
	            printf("*%c", temp);
	          }
          else if(eC == 127)
	          {
	            printf("*!");
	          }
        else if(eC == '*')
	        {
	          printf("**");
	        }
        else if(eC > 126 || eC < 32)
	        {
	          printf("Error\n");
	          skipLine();
	          return 0;
	        }
        else
	        {
	          printf("%c",eC);
	        }
        c = getchar();
      }

    return 0;
  }
/*decryption method, uses the same algorithm as encryption */
int decryption()
{
  char c;
  char toDecrypt;
  char dC;
  int firstDone;
  unsigned long randomVal;
  if(firstRandom == 1)
    {
      randomVal = readLCGs();
      if(randomVal == 555)
        {
          return 0;
        }
      firstDone = 0;
      firstRandom--;
    }
  c = getchar();
  if(c == '\n' || c == EOF)
    {
      return 0;
    }
  while(c!= '\n' || c!= EOF){
    toDecrypt = c;
    if(c == '\n' || c == EOF)
      {
        return 0;
      }
    if(firstDone >= 1)
      {
  randomVal = readLCGs();
  if(randomVal == 555)
    {
      if(skipLine() == 9)
        {
          return 0;
        }
      else
        {
          return 0;
        }
    }
      }
    firstDone++;
    /*checks for special characters */
    if(c == '*')
      {
  c = getchar();
  if(c == '*')
    {
      toDecrypt = '*';
    }
  else if(c == '!')
    {
      toDecrypt = 127;
    }
  else
    {
      toDecrypt = c - '?';
    }
  }
  dC = toDecrypt^(randomVal%128);
  if(dC < 32)
    {
      printf("Error");
      if(skipLine() == 9)
        {
          return 0;
        }
    }
  printf("%c",dC);
  c = getchar();
  toDecrypt = c;
}


  return 0;
}

/*main contains most of the logic and some error checking and it uses global ints and resets them every new line */
int main(void)
{
  int run = 1;
  int numLines = 1;
  while(run == 1)
    {
      encrypt = 0;
      decrypt = 0;
      specialError = 0;
      error = 0;
      genLCG = 1;
      firstRandom = 1;
      getMode();
    if(error == 1)
      {
        printf("%5d) ",numLines);
        printf("Error\n");
        if(skipLine() == 9) /*if skipLine() returns 9 which is '\n' then numLines is increased */
          {
            numLines++;
          }
        else /*if skipLine() returns EOF then it stops running. */
          {
            run = 0;
          }
      }
    else if(encrypt == 1)
      {
        printf("%5d) ",numLines);
        encryption();
        if(specialError == 0)
          {
            printf("\n");
          }
        numLines++;
      }
    else if(decrypt == 1)
      {
        printf("%5d) ",numLines);
        decryption();
        if(specialError == 0)
          {
            printf("\n");
          }
        numLines++;
      }
    else if(eof == 1)
      {
        run = 0;
      }
    else
      {
        run = 0;
      }
    }
  return 0;
}
