#ifndef bst_included		/* prevent multiple inclusion */
#define bst_included


/* a Binary Search Tree item */
typedef struct BSTItem_s {
  struct BSTItem_s *left;
  struct BSTItem_s *right;
  char *employee;
} BSTItem;

/* a list of BSTItems */
typedef struct {
  BSTItem *root;
} BSTree;

extern int bstDoCheck;		/* set true for paranoid consistency checking */

/* create a new tree */
BSTree *bstAlloc();

/* free memory associated with a list, discarding all items it contains */
void BSTFree(BSTree *tp);

/* append a copy of str to end of list */
void BSTAdd(BSTree *tp, char *s);

/* Delete all elements off of the list */
void BSTMakeEmpty(BSTree *tp);

/* print list membership.  Prints default mesage if message is NULL */
void BSTPrint(BSTree *tp);
#endif	/* included */
