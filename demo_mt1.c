#include "stdio.h"

union u1 {
  struct s1 *h; //8
  struct s2 *i; //8
  int j; //4 
};             


struct s1 {
  char a[2];
  int b[4];              
  union u1 c;
};

struct s2 { 
  struct s1 *d;
  short e;
  int f[6];
  struct s2 *g;
};

union u{
  float v;
  char s[5];
};

char proc1(union u1 *x)
{
  return x->h->a[1];
}

int main()
{
    struct s1 s1;

    struct s2 s2;

    union u1* u;

    union u quiz;

    
    proc1(u);


    return 0;
}