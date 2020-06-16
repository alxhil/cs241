#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct ListNode
{
  int data;
  struct ListNode* next;
};

/* Alloc a new node with given data. */
struct ListNode* createNode(int data);

/* Insert data at appropriate place in a sorted list, return new list head. */
struct ListNode* insertSorted(struct ListNode* head, int data);

/* Remove data from list pointed to by headRef, changing head if necessary.
 * Make no assumptions as to whether the list is sorted.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeItem(struct ListNode** headRef, int data);

/* Treat list as a stack. (LIFO - last in, first out)
 * Insert data at head of list, return new list head. */
struct ListNode* pushStack(struct ListNode* head, int data);

/* Treat list as a stack. (LIFO - last in, first out)
 * Remove and return data from head of non-empty list, changing head.
 * Memory for removed node should be freed. */
int popStack(struct ListNode** headRef);

/* Return length of the list. */
int listLength(struct ListNode* head);

/* Print list data on single line, separating values with a comma and
 * a space and ending with newline. */
void printList(struct ListNode* head);

/* Free memory used by the list. */
void freeList(struct ListNode* head);

/* Reverse order of elements in the list */
void reverseList(struct ListNode** headRef);

#endif
