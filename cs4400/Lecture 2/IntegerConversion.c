#include <stdio.h>

int main()
{
    char c = -5;
    int i = c;
    unsigned u = i;
    unsigned u2 = c;
    printf("%d %u %u\n", i, u, u2);
    return 0;
}