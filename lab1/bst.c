#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bst.h"

int bstDoCheck = 1;		/* set true for paranoid consistency checking */

#define doCheck(_bp) (bstDoCheck)

/* create a new list */
BSTree *bstAlloc()
{
  BSTree *tp = (BSTree *)malloc(sizeof(BSTree));
  tp->root = 0;
  doCheck(tp);
  return tp;
}

/* recycle a list, discarding all items it contains */
void BSTFree(BSTree *tp)
{
  doCheck(tp);
  BSTMakeEmpty(tp);
  free(tp);
}

/*Delete all elements of the tree */
void deleteTree(BSTItem *current){
  BSTItem *leftChild = current->left;
  BSTItem *rightChild = current->right;

  if(leftChild != 0){
    deleteTree(leftChild);
  }
  if(rightChild !=0){
    deleteTree(rightChild);
  }
  free(current);

}
void BSTMakeEmpty(BSTree *tp)
{
  doCheck(tp);
  deleteTree(tp->root);
  doCheck(tp);
}
  
void AddEmployee(BSTree *tp, BSTItem *current, char *s){

  if(current == NULL){
      current = (BSTItem *)malloc(sizeof(BSTItem));
      char *copy = malloc(sizeof(s));
      strcpy(copy, s);
      current->employee = copy;
      current->left = 0;
      current->right = 0;
      tp->root = current;
      return;
  }
  
  int result = strcmp(s, current->employee);
  if(result < 0){
    if(current->left == NULL){
      BSTItem *i;
      i = (BSTItem *)malloc(sizeof(BSTItem));
      char *copy = malloc(sizeof(s));
      strcpy(copy, s);
      i->employee = copy;
      current->left = i;
      i->left = 0;
      i->right = 0;
    }
    else{
      AddEmployee(tp, current->left, s);
    }
  }
  else if(result > 0){
    if(current->right == NULL){
      BSTItem *i;
      i = (BSTItem *)malloc(sizeof(BSTItem));
      char *copy = malloc(sizeof(s));
      strcpy(copy, s);
      i->employee = copy;
      i->left = 0;
      current->right = i;
      i->right = 0;
    }
    else{
      AddEmployee(tp, current->right, s);
    }
    //right
  }
  else{
    return;
  }
}


void BSTAdd(BSTree *tp, char *s){
  AddEmployee(tp, tp->root, s);

}

/* print list membership.  Prints default mesage if message is NULL */
void BSTPrintAll(BSTItem *current){
  if(current == NULL){
    return;
  }
  
  BSTItem *leftChild = current->left;
  BSTItem *rightChild = current->right;

  BSTPrintAll(leftChild);
  printf("%s\n", current->employee);
  BSTPrintAll(rightChild);
}

void BSTPrint(BSTree *tp)
{
  printf("\nEmployees: \n");
  BSTPrintAll(tp->root);
}




int main(){
  FILE *file;
  BSTree *tree= bstAlloc();

  file = fopen("test.txt", "a+");
  if(!file){
    printf("No file");
    exit(0);
  }
  char c;
  char *str;
  
  c = fgetc(file);
  int i = 0;
  while(c != EOF){
    if(c != '\n'){
      str[i] = c;
      i++;
    }
    else{
      str[i] = 0;
      printf("%s\n", str);
      BSTAdd(tree, str);
      i = 0;
    }
    c = fgetc(file);
  }
    
  
    
  int answer = 0;
  printf("Welcome to ACME Solutions.\n\nEnter the option number:");
  while(1){
  printf("\n1) Add New Employee\n2) Remove Employee\n3) Show All Employee Names\n4) Exit\n"  );
  scanf("%d", &answer);
  char *name = malloc(50);
  switch(answer){
  case 1:
    printf("Enter name of new employee:");
    scanf(" %[^\n]", name);
    printf("%s\n", name);
    BSTAdd(tree, name);
    fprintf(file, "%s\n", name);
    break;
    
  case 2:
    printf("Enter name of employee to be removed:");
    scanf("%s", name);
    //    BSTRemove(tree, name);
    break;

  case 3:
    BSTPrint(tree);
    break;

  case 4:
    fclose(file);
    exit(0);
    
  }
  }
  return 0;
}

