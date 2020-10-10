#include "stdio.h"

int addition(int a, int b)
{
    return a+b;
}

int main()
{
    int a = 3;
    int b = 5;

    int c = addition(a, b);
    return 0;
}