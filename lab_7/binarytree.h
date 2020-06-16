#ifndef BINARYTREE_H
#define BINARYTREE_H

struct TreeNode
{
  int data;
  struct TreeNode* left;
  struct TreeNode* right;
};

/* Alloc a new node with given data. */
struct TreeNode* createNode(int data);

/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(struct TreeNode* root, int data);

/* Remove data from BST pointed to by rootRef, changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 *   successor in the two-child case.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeBST(struct TreeNode** rootRef, int data);

/* Return minimum value in non-empty binary search tree. */
int minValueBST(struct TreeNode* root);

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root);

/* A tree is balanced if both subtrees are balanced and
 * the difference in height between the subtrees is no more than 1.
 * Return 1 if tree is balanced, 0 if not. */
int isBalanced(struct TreeNode* root);

/* Return 1 if tree is a binary search tree, 0 if not. */
int isBST(struct TreeNode* root);

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(struct TreeNode* root);

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root);

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root);

#endif
