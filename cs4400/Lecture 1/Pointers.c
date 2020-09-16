#include <stdio.h>

int main()
{
    int v = 5;
    int* p = &v;

    v = 6;
    printf("Resides at %p is %d.\n", p, *p);
    *p = 7;
    printf("Resides at %p is %d.\n", p, *p);
    printf("Resides at %p is %d.\n", p, p[0]);
    return 0;
}