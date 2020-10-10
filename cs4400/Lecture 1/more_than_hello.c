/*
 * Program: Hello World
 * Author: P. (Saday) Sadayappan
 * CS4400 Lecture 1, 8/24/20
 * Compile using: gcc -o hello2 more_than_hello.c
 * Run:           ./hello2
 */
#include "stdio.h"
int main (void) {
  printf("hello, world\n");

  // declaration, assignment and printing an integer
  int course = 4400;
  printf("hello, CS %d\n",course);

  // declaration, assignment and printing an integer array
  int prereq[2];
  prereq[0] = 3810;
  prereq[1] = 3505;
  printf("I hope you've taken %d and %d\n", prereq[0], prereq[1]);

  // Array names are address/pointers
  printf("Address of \'prereq\' is %p\n",prereq);
  printf("Address of prereq using hex is %x\n",prereq);

  // Declaration, assignment and display of pointer to an integer
  int *ptr = prereq;
  printf("Value of ptr: %p\n", ptr);
  printf("What ptr points to: %d\n", *ptr);
  printf("What happens if we print this: %d\n", *(ptr+1));

  // The address-of operator & can be used to set a pointer
  ptr = &course;
  printf("Value of ptr: %p\n", ptr);
  printf("What ptr points to: %d\n", *ptr);
  
  return 0;
} 
