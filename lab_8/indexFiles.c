#include <stdlib.h>
#include <stdio.h>
#include <string.h> /*To use strcpy */
void readInFile(char* fn, struct HTable* table)
{
  FILE* file;
  char* wordToAdd;
  char lettersIn[100]; /*This is assuming there are no words bigger than 100*/
  int i;
  int d;
  d = 0;
  file = fopen(fn,"r");
  for(i = 0; i < 100; i++)
    {
      lettersIn[i] = '\0'; /*Sets entire char array to null terminators*/
    }
  while((c=fgetc(file)) != EOF)
    {
      if(c == 32) /*whitespace ascii num */
	{
	  strcpy(lettersIn,wordToAdd);
	  table->table->token = wordToAdd;
	  table->table->next;
	  d = 0;
	  for(i = 0; i < 100; i++)
	    {
	      lettersIn[i] = '\0';
	    }
	}
      else if(c >= 97 && c <=122) /*lowercase a-z */
	{
	  lettersIn[d] = c;
	  d++;
	}
      else if(c >= 65 && c <=90) /*uppercase A-Z */
	{
	  c = c + 32;
	  lettersIn[d] = c;
	  d++;
	}
    }
}
