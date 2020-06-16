#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "indexFiles.h"
#include "graphUtils.h"

int main(int argv,char** argc)
{
  struct HTable* table;
  struct graph* g;
  g = readGraph(argc[1]); /*Reading in graph */
  if(g != NULL) /*Calculating page rank */
    {
      calculatePageRank(g); 
    }
  readInFile(argc[2],table); /* reads in file */
  while(table != NULL)
    {
      insert(table->table, table); /* insert functionality */
      table->table->next;
    }
  if(argc[3] != NULL){
    lookup(argc[3], table); /* lookup funtionality */
  }
}
