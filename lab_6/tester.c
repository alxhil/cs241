
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> /* provides EXIT_SUCCESS */

#define DEBUG 0
#define MAP_LENGTH 28

enum cipherModeEnum {ENCRYPT, DECRYPT};
enum cipherModeEnum cipherMode;

unsigned long lcg_c;
unsigned long lcg_m;
unsigned long lcg_a;
unsigned long lcg_x;
int cipherMap[MAP_LENGTH];

int status;
const int CLEAR = 0;
const int OK = 1;
const int END_OF_LINE = 2;
const int END_OF_FILE = 4;
const int ERROR = 8;


/**********************************************************************/
/* skipToEndOfLine(void)                                              */
/* Helper function that reads characters from the                     */
/* standard input stream (stdin) until '\n' or EOF.                   */
/*                                                                    */
/* None of the characters read are saved.                             */
/*                                                                    */
/* If '\n' is read, sets the END_OF_LINE flag of global field status. */
/* If EOF is read, sets the END_OF_FILE flag of global field status.  */
/**********************************************************************/
void skipToEndOfLine(void)
{
  char c;
  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }
  if (c == '\n')
    {
      status = END_OF_LINE;
    }
  if (c == EOF)
    {
      status = END_OF_FILE;
    }
}

/***********************************************************************/
/* readCipherMode(void)                                                */
/*   Reads one character from the standard input stream.               */
/*   Sets the global variable cipherMode to ENCRYPT or DECRYPT if the  */
/*     character read is an 'e' or a 'd'.                              */
/*                                                                     */
/* Returns:                                                            */
/*   OK if an 'e' or 'd' was read.                                     */
/*   END_OF_LINE if '\n' was read.                                     */
/*   END_OF_FILE if EOF was read.                                      */
/*   otherwise ERROR.                                                  */
/***********************************************************************/
int readCipherMode(void)
{
  char c = getchar();
  if (c == 'e')
    {
      cipherMode = ENCRYPT;
      return OK;
    }
  if (c == 'd')
    {
      cipherMode = DECRYPT;
      return OK;
    }
  if (c == '\n')
    {
      return END_OF_LINE;
    }
  if (c == EOF)
    {
      return END_OF_FILE;
    }
  else return ERROR;
}

/******************************************************************************/
/*  readDataBlock(char data[])                                                */
/*    Reads one block of cipher data from the standard input stream.          */
/*    Reading stops when a full block is read or when '\n' is read.           */
/*    An error is triggered if any byte code (other than '\n') is read        */
/*      that is not a printable ASCII character: [32, 126].                   */
/*                                                                            */
/* Parameters:                                                                */
/*    data[]: a null-terminated array of size 5 into which the data is read.  */
/*      All elements of data are initialized to '\0'.                         */
/*      If global variable cipherMode == ENCRYPT, then each legal character   */
/*        read is copied into data[].                                         */
/*      If global variable cipherMode == DECRYPT, then character codes [0,31] */
/*        and 127 might be represented as two-byte codes starting with '*'.   */
/*      This function converts any such two-character codes to the single     */
/*        ASCII code [0,127]. Therefore, this function may read as many as    */
/*        eight characters form the standard input stream.                    */
/*                                                                            */
/* Returns:                                                                   */
/*   OK | END_OF_LINE | END_OF_FILE | ERROR                                   */
/******************************************************************************/
int readDataBlock(char data[])
{
  int i, j;
  char next;
  char c;
  for(i = 0; i <= 4; i++)
    {
      data[i] = '\0';
    }
  if (cipherMode == ENCRYPT)
    {
      for(j = 0; j < 4; j++)
	{
	  c = getchar();
	  if ((c < 32 || c > 126) && c != '\n')
	    {
	      return ERROR;
	    }
	  if (c == EOF)
	    {
	      return END_OF_FILE;
	    }
	  if (c == '\n')
	    {
	      return END_OF_LINE;
	    }
	  else
	    {
	      data[j] = c;
	    }
	}
      return OK;
    }
  else if (cipherMode == DECRYPT)
    {
      for(j = 0; j < 4; j++)
	{
	  c = getchar();
	  if (c == EOF)
	    {
	      return END_OF_FILE;
	    }
	  if (c == '\n')
	    {
	      return END_OF_LINE;
	    }
	  if (c == '*')
	    {
	      next = getchar();
	      if (next == '%')
		{
		  data[j] = 127;
		}
	      else if (next == '*')
		{
		  data[j] = '*';
		}
	      else
		{
		  data[j] = (next - '?');
		}
	    }
	  else
	    {
	      data[j] = c;
	    }
	}
      return OK;
    }
  return OK;
}

/**********************************************************************/
/* productOfUniquePrimeFactors(unsigned long n)                       */
/* Helper function that finds the product of the parameter's          */
/* unique prime factors. This function is called by the               */
/* calculateLCG_a(unsigned long LCG_m) function in order to calculate */
/* the global variable value lcg_a.                                   */
/*                                                                    */
/* Parameters:                                                        */
/*   unsigned long integer global variable lcg_m                      */
/*                                                                    */
/* Returns: Product for parameter's unique prime factors              */
/**********************************************************************/
long productOfUniquePrimeFactors(unsigned long n)
{
  long test = 2;
  long product = 1;
  while (test <= n)
    {
      if (n % test == 0)
	{
	  product *= test;
	  while(n % test == 0)
	    {
	      n /= test;
	    }
	}
      test++;
    }
  return product;
}

/********************************************************************************/
/*  calculateLCG_a(unsigned long LCG_m)                                         */
/*    Given m of a Linear Congruential Generator (LCG): Xn+1 = (aXn + c) mod m  */
/*      This method finds an a that will yield a full period.                   */
/*      The value of a is:                                                      */
/*        a = 1+2p, if 4 is a factor of m, otherwise, a = 1+p.                  */
/*        p = (product of m's unique prime factors).                            */
/*        0 < a < m (otherwise error).                                          */
/*                                                                              */
/*    This is a reusable utility function.                                      */
/*    It does not access any global variables.                                  */
/*    It can be moved to a different file.                                      */
/*                                                                              */
/* Parameters:                                                                  */
/*    LCG_m:     m of an LCG.                                                   */
/*                                                                              */
/* Returns:                                                                     */
/*    a of the LCG or 0 if there was an error.                                  */
/********************************************************************************/
unsigned long calculateLCG_a(unsigned long LCG_m)
{
  long p = productOfUniquePrimeFactors(LCG_m);
  if (LCG_m % 4 == 0)
    {
      lcg_a = 1+2*p;
    }
  else
    {
      lcg_a = 1+p;
    }
  if (lcg_a < lcg_m)
    {
      return lcg_a;
    }
  else
    {
      return 0;
    }
}

/******************************************************************************/
/* readPositiveLong(char delimiter)                                           */
/*   Reads characters from the standard input stream until either             */
/*   the character read equals the delimiter or until an error.               */
/*                                                                            */
/*   This is a reusable utility function.                                     */
/*   It does not access any global variables.                                 */
/*   It can be moved to a different file.                                     */
/*                                                                            */
/*   An error occurs if:                                                      */
/*    1) A character is read that is not a digit (0-9) and not the delimiter. */
/*    2) More than 20 digits are read                                         */
/*    3) The compiler's representation of an unsigned long is <64 bits.       */
/*                                                                            */
/*   Returns                                                                  */
/*    If no error, returns an unsigned long defined by the digits read.       */
/*    If an error, returns 0.                                                 */
/******************************************************************************/
unsigned long readPositiveLong(char delimiter)
{
  int max = 20;
  char temp[21];
  int i = 0;
  int j;
  unsigned long n = 0;
  for (j = 0; j < 21; j++)
    {
      temp[j] = '\0';
    }

  char c = getchar();
  while (c != ',')
    {
      if (c >= '0' && c <= '9')
	{
	  temp[i] = c;
	  i++;
	}
      else
	{
	  return 0;
	}
      c=getchar();
    }

  if (i > max)
    {
      return 0;
    }

  return n = strtoul(temp, NULL, 10);
}

/****************************************************************/
/* readKey(void)                                                */
/*                                                              */
/*   Calls readPositiveLong and sets the global variable lcg_m. */
/*   Calls readPositiveLong and sets the global variable lcg_c. */
/*   Calls calculateLCG_a and sets the global variable lcg_a.   */
/*   Sets the global variable lcg_x.                            */
/*                                                              */
/* Return: OK | ERROR                                           */
/****************************************************************/
int readKey(void)
{
  char delimiter = ',';
  lcg_m = readPositiveLong(delimiter);
  lcg_c = readPositiveLong(delimiter);
  lcg_a = calculateLCG_a(lcg_m);
  lcg_x = lcg_c;

  if (lcg_c <=0 || lcg_m <= 0 || lcg_a <= 0)
    {
      return ERROR;
    }
  else
    {
      return OK;
    }
}

/***************************************************************************/
/* buildMap(void)                                                          */
/*                                                                         */
/* Uses the global variables lcg_a, lcg_c, lcg_m and lcg_x to define the   */
/*   global array: cipherMap[] such that cipherMap[i] = k indicates that   */
/*   on encryption, bit i is moved to bit k and the reverse on decryption. */
/*                                                                         */
/* When this function returns, lcg_x will have been updated 28 steps       */
/*   in the LCG.                                                           */
/*                                                                         */
/* This method does not return a value because there is no reason for it   */
/*   to fail.                                                              */
/***************************************************************************/
void buildMap(void)
{
  unsigned long temp[29];
  unsigned long gi[28];
  int index[56];
  int i, k;
  int m, n, p;
  int used = 0;
  int open =0;
  int count = 0;
  int b;

  for (m = 0; m < 28; m++)
    {
      temp[m]= 0;
      gi[m]=0;
    }
  for (m = 0; m < 56; m++)
    {
      index[m]=0;
    }
  temp[0] = lcg_x;
  for (i = 1; i <= 28; i++)
    {
      temp[i] = ((lcg_a * lcg_x) + lcg_c) % lcg_m;
      lcg_x = temp[i];
    }
  for (p = 0; p < 28; p++)
    {
      gi[p] = (temp[p] % (28-count));
      count++;
    }
  for (k = 0; k < 28; k++)
    {
      for(n = 0; n <= gi[k]+used; n++)
	{
	  if (index[n] != 0)
	    {
	      used++;
	    }
	}
      open = gi[k] + used;
      cipherMap[k] = open;
      index[open] = k+1;
      used = 0;
    }
  if (DEBUG)
    {
      for (b = 0; b < 28; b++)
	{
	  printf("%d ", cipherMap[b]);
	}
    }
}

/*****************************************************************************/
/* encrypt(char data[])                                                      */
/*   Uses the global variable cipherMap to encrypt the data block in data[]. */
/*   The encrypted data is sent to the standard output stream.               */
/*   The encrypted data will always be 4 to 8 bytes long.                    */
/*   Encrypted byte codes [0,31], 127 and '*' are converted to 2-byte        */
/*     printable ASCII characters.                                           */
/*                                                                           */
/* Parameters: data[]: Must be a null terminated char[] of size 5.           */
/*                                                                           */
/* Return: OK | ERROR                                                        */
/*****************************************************************************/
int encrypt(char data[])
{
  char cipher[4];
  int i, j, k, m;
  int flag = 0;
  int byte;
  int bit;
  int c_byte;
  int c_bit;
  char printable;

  for (i = 0; i < 4; i++)
    {
      cipher[i] = '\0';
    }

  for(j = 0; j < 28; j++)
    {
      byte = j / 7;
      bit = j % 7;

      if(data[byte] & (1<<bit))
	{
	  c_byte = cipherMap[j] / 7;
	  c_bit = cipherMap[j] % 7;
	  cipher[c_byte] |= (1<<c_bit);
	}
    }

  for(m = 0; m < 4; m++)
    {
      if (data[m] != 0)
	{
	  flag = 1;
	}
    }

  if(flag)
    {
      for(k = 0; k < 4; k++)
	{
	  if(cipher[k] < 32)
	    {
	      printable = ('?' + cipher[k]);
	      printf("*%c", printable);
	    }
	  else if(cipher[k] == 127)
	    {
	      printf("*");
	      putchar('%');
	    }
	  else if (cipher[k] == '*')
	    {
	      printf("**");
	    }
	  else if (cipher[k] > 126)
	    {
	      printf("Error\n");
	      skipToEndOfLine();
	      return ERROR;
	    }
	  else printf("%c", cipher[k]);
	}
    }
  else printf("");
  return OK;
}

/********************************************************************************/
/* decrypt(char data[])                                                         */
/*   Uses the global variable cipherMap to decrypt the data block in data[].    */
/*   The decrypted data is sent to the standard output stream.                  */
/*   The decrypted data will always be 1 to 4 bytes long.                       */
/*   If a decrypted character is '\0' it means that the data block was a        */
/*     parcial block from the end of the line. '\0' characters are not printed. */
/*   Any other decrypted byte that is not a printable ASCII character is an     */
/*     error.                                                                   */
/*                                                                              */
/* Parameters: data[]: Must be a null terminated char[] of size 5.              */
/*                                                                              */
/* Return: OK | ERROR                                                           */
/********************************************************************************/
int decrypt(char data[])
{
  char plain_text[4];
  int i, j, k;
  int byte;
  int bit;
  int d_byte;
  int d_bit;
  char printable;

  for (i = 0; i < 4; i++)
    {
      plain_text[i] = '\0';
    }
  for(j = 0; j < 28; j++)
    {
      byte = cipherMap[j] / 7;
      bit = cipherMap[j] % 7;

      if(data[byte] & (1<<bit))
	{
	  d_byte = j / 7;
	  d_bit = j % 7;
	  plain_text[d_byte] |= (1<<d_bit);
	}
    }

  for(k = 0; k < 4; k++)
    {
      if(plain_text[k] == '\0')
	{
	  printf("");
	}
      else if(plain_text[k] > 127 || plain_text[k] < 32)
	{
	  return ERROR;
	}
      else printf("%c", plain_text[k]);
    }
  return OK;
}


int main()
{
  int inputLineNumber = 0;
  status = CLEAR;

  char data[5];
  data[4] = '\0';

  while (status != END_OF_FILE)
    {
      status = CLEAR;
      inputLineNumber++;

      status = readCipherMode();
      if (DEBUG) printf("readCipherMode::mode=%d status=%d\n",cipherMode,status);

      if ((status & END_OF_FILE) == 0)
	{
	  printf("%5d) ", inputLineNumber);
	}
      if (status == OK)
	{
	  status = readKey();
	  if (DEBUG)
	    {
	      printf ("\tKey: m=%lu c=%lu a=%lu x=%lu status=%d\n",
		      lcg_m, lcg_c, lcg_a, lcg_x, status);
	    }
	}

      while (status == OK)
	{
	  buildMap();
	  status = readDataBlock(data);
	  if (DEBUG) printf("\treadDataBlock::data=%s status=%d\n",data,status);
	  if ((status & ERROR) == 0)
	    {
	      if (cipherMode == ENCRYPT) status |= encrypt(data);
	      else status |= decrypt(data);
	    }

	}
      if (status & ERROR)
	{
	  puts("Error");
	  skipToEndOfLine();
	}
      else puts("");
    }
  return EXIT_SUCCESS;
}
