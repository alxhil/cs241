/* ALEX HILL */
/* CS-241-005*/
/* APRIL 19  2018 */

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

/*Hash takes in a struct elt which has a token, you take the token and add up all of the ascii letters inside then return that value */
int hash(struct HashElt* elt)
{
  char* word=elt->token;
  int overAll;
  overAll = 0;
  /*The error checking will be when I am making a token and setting to lowercase will be in the token making as well */
  while(word[i])
    {
      overAll=overAll+word[i];
      i++;
    }
  return overAll;
}
/*Inserts a struct HashElt* into  */
void insert(struct HashElt* elt, struct HTable* table)
{
  int toInsert = hash(elt);
  int modulusR;
  int n;
  n = 1;
  modulusR = toInsert%table->size; /*Gives modulus of overall % size of array */
  while(n)
    {
      if(table->table[modulusR] == NULL) /*If the spot in this part of the array of pointers is empty*/
	{
	  table->table[modulusR] = elt; /*set the value of that array = to the elt you pass in */
	  table->n++; /*increases number of elements in area */
	  n--; /*stops while loop */
	}
      else
	{
	  table->table[modulusR]->next; /*looks to next value at that value of the array of pointers */
	}
    }
}


struct HashElt* lookup(char* key, struct HTable* table)
{
  int hashVal;
  int run;
  struct HashElt* look;
  struct HashElt* toReturn;
  look->token = key;
  hashVal = hash(look);
  look = table->table[hashVal%table->size];
  run = 1;
  while(table != NULL)
    {
      if(hashVal == look)
       {
	 return look;
       }
    }
  return toReturn;
}
