#include <stdio.h>

int return_three()
{
  int a = 1;
  int b = 2;
  return a + b;
}

int main()
{
  int a = 0;
  int b = 1;
  int c = 2;
  int d = return_three();

  return 0;
}
