#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bst.h"

int bstDoCheck = 1;		/* set true for paranoid consistency checking */

#define doCheck(_bp) (bstDoCheck)

/* create a new tree */
BSTree *bstAlloc()
{
  BSTree *tp = (BSTree *)malloc(sizeof(BSTree));
  tp->root = 0;
  doCheck(tp);
  return tp;
}

/* recycle a tree, discarding all items it contains */
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

//add new node with employee name to the tree
void AddEmployee(BSTree *tp, BSTItem *current, char *s){
  //create the new node and add it to tree
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
  //checks the vvalue of the string so it can place it in the correct place in the tree
  int result = strcmp(s, current->employee);
  //places employee in the left part
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
  //places employee to the right
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
  }
  //does not add employee if it's already on the tree
  else{
    return;
  }
}

//call add method with the tree
void BSTAdd(BSTree *tp, char *s){
  AddEmployee(tp, tp->root, s);

}

/* print tree membership */
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

//call print method with tree
void BSTPrint(BSTree *tp)
{
  printf("\nEmployees: \n");
  BSTPrintAll(tp->root);
}

//get the largest node from the left child
char *getLargestfromLeft(BSTItem *current){
 
  current = current->left;
  while(current->right != NULL){
    current = current->right;
  }
  char *copy = malloc(sizeof(current->employee));
  strcpy(copy, current->employee);
  return copy;
}

//get the smallest node from the right child
char *getSmallestfromRight(BSTItem *current){
  current = current->right;
  while(current->left != NULL){
    current = current->right;
  }
  char *copy = malloc(sizeof(current->employee));
  strcpy(copy, current->employee);
  return copy;

}

//removes employee node from the tree
BSTItem *removeItem(BSTItem *current, char *str){
  
  if(current == NULL){
    return current;
  }

  if(strcmp(current->employee, str) == 0){
    printf("Found!\n");
    //remove if it's leaf
    if(current->left == NULL && current->right == NULL){
      free(current);
      return 0;
    }
    //if there is no left child get smallest from right child
    else if(current->left == NULL){
      current->employee = getSmallestfromRight(current);
      current->right = removeItem(current->right, current->employee);
      
    }
    //if there is no right child get largest from left child
    else if(current->right==NULL){
      current->employee = getLargestfromLeft(current);
      current->left = removeItem(current->left, current->employee);
    }
    else{
      //remove desired node and replace with the largest from the left child
      current->employee = getLargestfromLeft(current);
      current->left = removeItem(current->left, current->employee);
    }
  }
  else if(strcmp(str, current->employee) > 0){
    current->right = removeItem(current->right, str);
  }
  else{
    current->left = removeItem(current->left,str);
  }

}
//call remove method with tree root
void BSTRemove(BSTree *tp, char *str){
  tp->root = removeItem(tp->root, str);
}

//write updated tree to file  in preorder
void treeFile(BSTItem *current, FILE *file){
  if(current == NULL){
    return;
  }
  
  BSTItem *leftChild = current->left;
  BSTItem *rightChild = current->right;

  fprintf(file, "%s\n", current->employee);
  treeFile(leftChild, file);
  treeFile(rightChild, file);   
}


int main(){
  FILE *file;
  BSTree *tree= bstAlloc();

  file = fopen("tree.txt", "a+");
  if(!file){
    printf("No file");
    exit(0);
  }
  char c;
  char *str;
  //read file
  c = fgetc(file);
  int i = 0;
  while(c != EOF){
    if(c != '\n'){
      str[i] = c;
      i++;
    }
    else{
      str[i] = 0;
      BSTAdd(tree, str);
      i = 0;
    }
    c = fgetc(file);
  }
    
  
  //interface
  int answer = 0;
  printf("Welcome to ACME Solutions.\n\nEnter the option number:");
  while(1){
  printf("\n   1) Add New Employee\n   2) Remove Employee\n   3) Show All Employee Names\n   4) Exit\n"  );
  scanf("%d", &answer);
  char *name = malloc(50);
  switch(answer){
  case 1:
    printf("Enter name of new employee:");
    scanf(" %[^\n]", name);
    BSTAdd(tree, name);
    fprintf(file, "%s\n", name);
    break;
    
  case 2:
    printf("Enter name of employee to be removed:");
    scanf(" %[^\n]", name);
    BSTRemove(tree, name);
    break;

  case 3:
    BSTPrint(tree);
    break;

  case 4:
    fclose(file);
    file = fopen("tree.txt", "w");
    //write tree contents to file
    treeFile(tree->root, file);
    fclose(file);
    exit(0);
    
  }
  }
  return 0;
}

