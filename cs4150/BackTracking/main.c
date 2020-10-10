#include "stdio.h"

union u1 {
  int k[3];
};

int main()
{
    union u1 x;

    int size = sizeof(x);

    printf("%d\n", size);
    return 0;
}