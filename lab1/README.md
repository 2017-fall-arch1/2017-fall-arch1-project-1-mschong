# Project 1: Personel Management System

This directory contains:
* code that implements a binary searh tree of strings

The demo program reads lines from tree.txt.
Each line is appended onto a binary search tree.
Asks user what he/she wants to do. (Add, remove, or print).

This directory contains the following files:
 bst.h: header file of binary search tree structure & "public" interface functions
 bst.c: implementation of binary search tree
 tree.txt: contents of the tree

 

To compile:
~~~
$ make
~~~

To test it, try:
~~~
$ make demo
~~~

To delete binaries:
~~~
$ make clean
~~~

# Using the program #

Select option
  1. to add a new employee to the tree
  2. to remove an employee from the tree
  3. to print all employee names from the tree
  4. to exit

Adding Method:
* Once selected, enter name of the new employee
* Name is stored in a node and is added to the file
* If the name does not exist in the tree, the name will be placed in its respective place following the alphabetical order.
* Otherwise it it already exists, the name will not be added.

Removing Method:
* Once selected, enter name of the employee to be removed
* Searches for that name
* Once found, it is removed and replaced with the largest from the leftmost side or the smallest from the right side depending on the structure of the tree. This is done recursively to maintain the tree structure.

Print Method:
* Inorder printing

Exit:
* Writes the tree in preorder.
* Exits program
	  