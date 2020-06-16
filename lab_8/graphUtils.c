/*Alex Hill */
/*CS-241-005 */
/*5/4/2018 */
#include "graph.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* Uses depth first search to find the URL in the graph.
   Returns 1 if url is in the graph. */
struct graph* inQueue(struct graph* g, char* url);  
int getEdges(struct graph* g);
int outQueue(struct graph* g);
int depthFirstSearch(struct graph* g, char* url)
{  
  struct node* temp;
  struct node* currNode;
  currNode=g->firstNode;
  
  if(strcmp(currNode->url, url))
    {
      return 1;
    }
    while(currNode->next != NULL)
      {
	if(currNode->next != NULL)
	  {
	    temp = currNode->next;
	    currNode->visited++;
	  }
	else
	  {
	    if(currNode->next->next != NULL)
	      {
		currNode->next->next = temp;
	      }
	  }
	printf("%s",currNode->url);
      }
    return 0;

}

/* Uses breadth first search to find the URL in the graph.
     Returns 1 if url is in the graph. */
int breadthFirstSearch(struct graph* g, char* url)
{
  struct node* currNode;
  currNode = g->firstNode;
  while(currNode != NULL)
    {
      if(currNode->next != NULL)
	{
	  inQueue(g, url);
	}
      else
	{
	  currNode->visited++;	  
	}
      outQueue(g);
    }
  if(strcmp(url, currNode->url))
    {
      return 1;
    }
    else
      {
	return breadthFirstSearch(g,url);
      }
  return 0;
}
/* in queue for BFS */
struct graph* inQueue(struct graph* g, char* url)
{
  struct graph* newGraph;
  newGraph = createGraph();
  newGraph->firstNode->url = url;
  newGraph->firstNode->next = g->firstNode->next;
  return newGraph;
}
/* out queue for BFS */
int outQueue(struct graph* g)
{
  struct node* newGraph;
  int value;
  newGraph = g->firstNode;
  value = newGraph->next->visited;

  if(newGraph->next != NULL)
    {
      free(newGraph);
      return value;
    }
  return value;
}

/* calculates the pagerank of each node in the graph.*/
void calculatePageRank(struct graph* g)
{
  struct node* currNode;
  struct node* pastNode;
  int firstPR;
  float value;
  float firstVal;
  int i;
  int run;
  int edges;
  float pageRank;
  int normalPR;
  currNode = g->firstNode;
  pageRank = 0.0;
  normalPR = 0;
  run = 1;
  firstPR = 1;
  firstVal = .15;
  value = .85;
  run = 0;
  while(run)
    {
      for(i = 0; i < 100; i++)
	{
	  if(firstPR == 1)
	    {
	      currNode->pagerank = firstVal;
	      firstPR--;
	      normalPR++;
	      pastNode = g->firstNode->next;
	    }
	  if(normalPR == 1)
	    {
	      edges = getEdges(g);
	      pageRank = firstVal+(value*(pastNode->pagerank/edges));
	      currNode->pagerank = pageRank;
	      pastNode = g->firstNode;
	      if(currNode->next == NULL)
		{
		  run = 0;
		}
	    }
	}
    } 
}
int getEdges(struct graph* g)
{
  struct node* currNode;
  int numEdges;
  currNode = g->firstNode;
  numEdges = 0;
  while(currNode->next != NULL)
    {
      numEdges++;
    }
  return numEdges;
}
 
/* prints out each URL and their associated pagerank*/
 void printPageRank(struct graph* g)
{
  struct node* currNode;
  currNode = g->firstNode;
  while(currNode!=NULL)
    {
      printf("%s,%f", currNode->url, currNode->pagerank);
      currNode = currNode->next;
    }
}

/* reads in the graph from file and stores it in a graph object */
 struct graph* readGraph(char* s)
{
  struct graph* g;
  char* url1=malloc(sizeof(char)*50);
  char* url2=malloc(sizeof(char)*50);
  int isFull;
  FILE* file;
  char c;
  int index;
  g = createGraph();
  index = 0;
  isFull = 0;
  file = fopen(s, "r");
  while((c=fgetc(file)) != EOF)
    {
      if(isFull  == 0)
	{
	  if(c == ',')
	    {
	      isFull++;
	      index = 0;
	    }
	  else
	    {
	      url1[index] = c;
	      index++;
	    }
	}
      if(isFull == 1)
	{
	  if(c == '\n')
	    {
	      insertNode(g,url1);
	      insertNode(g,url2);
	      insertEdge(g,url1,url2);
	      url1=malloc(sizeof(char)*50);
	      url2=malloc(sizeof(char)*50);
	      isFull =0;
	    }
	  else
	    {
	      url2[index] = c;
	    }
	}
    }
  fclose(file);
  return g;
}
 
 int main(int arcv, char** argc)
 {
   readGraph(argc[1]);
   return 0;
 }
 
 
