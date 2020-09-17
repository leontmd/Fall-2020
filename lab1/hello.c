// Lab 1 - hello.c

#include <stdio.h>

char ctest(int a, int b)
{
    char t1 = a >= b;
    char t2 = &b <= &a;
    return t1 + t2;
}
main()
{
    char t = ctest(10, 20);
}
