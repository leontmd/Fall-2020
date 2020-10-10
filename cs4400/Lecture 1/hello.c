/*
 * Program: Hello World
 * Author: P. (Saday) Sadayappan
 * CS4400 Lecture 1, 8/24/20
 * Things we did after writing the code: 
 *   Compile and generate an exectuble file in ./hello: gcc -o hello hello.c
 *   Stop at generating assembly code in hello.s:       gcc -S hello.c
 *   Compile hello.c or hello.s to produce object file: gcc -c hello.s
 *                                                      gcc -c hello.c
 *   Link to produce an executable from object file:    gcc -o hello hello.o
 *   Produce a.out, default executable name:            gcc hello.c
 */

#include "stdio.h"
int main (void) {
  printf("hello, world\n");
  return 0;
} 
