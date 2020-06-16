#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char** argv)
{
  int i, n;
  struct ListNode* head = NULL;
  struct ListNode* stack = NULL;

  printf("empty list: ");
  printList(head);

  for(i = 0; i < 23; ++i)
  {
    n = (i*17+11) % 23;
    head = insertSorted(head, n);
    stack = pushStack(stack, n);
  }

  printf("filled list: ");
  printList(head);
  printf("list length = %d\n", listLength(head));

  printf("filled stack: ");
  printList(stack);
  printf("stack size = %d\n", listLength(stack));

  for(i = -4; i < 25; i+=4)
  {
    n = removeItem(&head, i);
    if(!n) printf("remove did not find %d\n", i);  
  }

  printf("list after removes: ");
  printList(head);
  printf("list length = %d\n", listLength(head));

  for(i = 0; i < 5; ++i)
  {
    printf("pop: %d\n", popStack(&stack));
  }

  printf("stack after pops: ");
  printList(stack);
  printf("stack size = %d\n", listLength(stack));

  reverseList(&head);
  printf("list after reverse: ");
  printList(head);

  freeList(head);
  head = NULL;

  freeList(stack);
  stack = NULL;

  return 0;
}
