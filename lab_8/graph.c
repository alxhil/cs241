/*************************************************/
/* Defines basic graph functionality (linked list*/
/* style to be used for Lab 8                    */
/*************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/************************************* 
 * Returns a pointer to a graph in memory
 * Creates a null graph.
 *************************************/
struct graph* createGraph(void)
{
  struct graph* newGraph;
  newGraph = (struct graph*) malloc(sizeof(struct graph));
  newGraph->firstNode = NULL;
  return newGraph;
}

/************************************* 
 * Takes in a pointer to a graph in memory.
 * Prints out all the nodes in this graph.
 *************************************/
void printGraphNodes(struct graph* g)
{
  struct node* currNode;
  currNode = g->firstNode;
  while (currNode!=NULL)
  {
    printf("%s\n", currNode->url);
    currNode = currNode->next;
  }
}

/************************************* 
 * Parameter: a pointer to a character array
 *            containing the URL for the new node
 * Returns a pointer to a node in memory
 * Creates a new node with only the URL instantiated
 * Helper function for insertNode
 *************************************/
struct node* createNode(char* url)
{
  struct node* newNode;
  newNode = (struct node *)malloc(sizeof(struct node));
  newNode->url = url;
  newNode->visited = 0;
  newNode->pagerank = 1;
  newNode->edges = NULL;
  newNode->next = NULL;
  return newNode;
}

/************************************* 
 * Parameters:- a pointer to the graph we're inserting into
 *            - a pointer to the URL to insert into the graph
 * Adds the node to the graph.
 * Edits the graph in memory, so returns nothing
 * It will allow multiple entries of the same URL.
 *************************************/
void insertNode(struct graph* g, char* url)
{
  struct node* newNode;
  newNode = createNode(url);
  /* first case: empty graph*/
  if (g->firstNode == NULL)
   {
     g->firstNode = newNode;
   }
  else
  /* second case: nonempty graph*/
  {
    struct node* currNode;
    currNode = g->firstNode;
    while(currNode->next != NULL)
    {
      currNode = currNode->next;
    }
    currNode->next = newNode;
  }
}


/************************************* 
 * Parameters: two pointers to the nodes on either end of the edge
 * Updates node1 to have node2 in its edge list
 * Helper function for insertEdge
 *************************************/
void createEdge(struct node* node1, struct node* node2)
{
  struct edge* newEdge;
  newEdge = (struct edge *)malloc(sizeof(struct edge));
  newEdge->next=NULL;
  newEdge->connectsTo = node2;
  /* first case: node1 has no existing edges*/ 
  if (node1->edges == NULL)
  {
    node1->edges = newEdge;
  }
  else
  /* second case: node1 has existing edges*/ 
  {
    struct edge* currEdge;
    currEdge = node1->edges;
    while (currEdge->next !=NULL)
    {
      currEdge = currEdge->next;
    }
    currEdge->next = newEdge;
  }
}

/************************************* 
 * Parameters:- a pointer to the graph we're inserting into
 *            - two pointers to the URLs on either end of the edge
 * Adds an edge to the graph from url1 to url2.
 * Edits the graph in memory, so returns nothing
 * It will allow a self edge.
 *************************************/

void insertEdge(struct graph* g, char* url1, char* url2)
{
  struct node* node1;
  struct node* node2;
  struct node* currNode;
  node1 = NULL;
  node2 = NULL;
  currNode = g->firstNode;
  while (currNode !=NULL)
  {
   /* use strcmp to see if url1 is the url we're looking at
      strcmp will return 0 if the same, a nonzero int otherwise*/ 
    if (strcmp(currNode->url, url1)==0)
    {
      node1 = currNode;
    }
    if (strcmp(currNode->url, url2)==0)
    {
      node2 = currNode;
    }
    currNode = currNode->next;
  }

  if ((node1 == NULL)| (node2 == NULL))
  {
    printf("%s\n","ERROR: Adding edge between one or more URLs that aren't in the graph.");
    return;
  }
  /* create edge from node1 to node2*/ 
  createEdge(node1, node2);
  /* if this was an undirected graph, we'd also have the following line
     createEdge(node2, node1); */
}
