/* Alex Hill  */
/* CS-241-005 */
/* 4/19/2018  */
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"


/* Alloc a new node with given data. */
struct ListNode* createNode(int data)
{
  /* from in-class slides */
  struct ListNode* newNode = malloc(sizeof(struct ListNode));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

/* Insert data at appropriate place in a sorted list, return new list head. */
struct ListNode* insertSorted(struct ListNode* head, int data)
{
  struct ListNode* new = createNode(data);
  struct ListNode* currentNode = head;
  /* Using ideas from https://www.geeksforgeeks.org/given-a-linked-list-which-is-sorted-how-will-you-insert-in-sorted-way/ */
  if (currentNode == NULL || currentNode->data > data)
  {
    new->next = currentNode;
    return new;
  }
  else
  {
    while (currentNode->next != NULL && currentNode->next->data < data)
    {
      currentNode= currentNode->next;
    }
    new->next=currentNode->next;
    currentNode->next = new;
    return head;
  }
}

/* Remove data from list pointed to by headRef, changing head if necessary.
 * Make no assumptions as to whether the list is sorted.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeItem(struct ListNode** headRef, int data)
{
 return 0;
}

/* Treat list as a stack. (LIFO - last in, first out)
 * Insert data at head of list, return new list head. */
struct ListNode* pushStack(struct ListNode* head, int data)
{
  struct ListNode* newNode;
  newNode = createNode(data);
  newNode->next = head;
  return newNode;
}

/* Return length of the list. */
int listLength(struct ListNode* head)
{
  int length;
  struct ListNode* oldHead;
  length = 0;
  oldHead = head;
  /* credit to https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/ */
  while(oldHead != NULL)
  {
    oldHead=oldHead->next;
    length++;
  }
  return length;
}

/* Treat list as a stack. (LIFO - last in, first out)
 * Remove and return data from head of non-empty list, changing head.
 * Memory for removed node should be freed. */
int popStack(struct ListNode** headRef)
{
  struct ListNode* newNode;
  int value;
  newNode = *headRef;
  value = newNode->data;
  (*headRef) = newNode->next;
  free(newNode);
  return value;
}

void printList (struct ListNode* head)
{
  int i;
  struct ListNode* temp;
  temp =head;
  i = 0;
  for (i=0;i<listLength(head);i++)
  {
    printf ("%d",temp->data);
    temp=temp->next;
  }
  printf("\n");
}

/* Free memory used by the list. */
void freeList (struct ListNode* head)
{
  struct ListNode* temp = head ;
  if (temp!=NULL)
  {
    freeList(temp->next);
    free(temp);
  }

}

/* Reverse order of elements in the list */
void reverseList(struct ListNode** headRef)
{
    /* credit to https://www.geeksforgeeks.org/reverse-a-linked-list/ */
    struct ListNode* previous   = NULL;
    struct ListNode* current = *headRef;
    struct ListNode* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *headRef = previous;
}
