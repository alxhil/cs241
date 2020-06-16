#ifndef GRAPH_H
#define GRAPH_H

struct node {
    char* url;
    int visited;
    float pagerank;
    struct edge *edges;
    struct node *next;
};

struct edge {
    struct node *connectsTo;
    struct edge *next;
};

struct graph {
    struct node *firstNode;
};

/*Create a new graph*/
struct graph* createGraph(void);

/* Insert a node into a graph */
void insertNode(struct graph* g, char* url);

/* Insert an edge into a graph between existing nodes */
void insertEdge(struct graph* g, char* url1, char* url2);

/* Prints out all the nodes of a graph, one per line */
void printGraphNodes(struct graph* g);

#endif
