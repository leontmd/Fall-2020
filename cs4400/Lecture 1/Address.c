#include <stdio.h>


int main()
{
    // %d means int
    // %f means double
    // %s means string
    // %p means address
    // %c means character
    printf("Ten and ten make %d\n", 10 + 10);

    printf("Hex 10 and hex 10 make %d\n", 0x10 + 0x10);

    printf("%p %p\n", main, printf);

    int v = 5;
    printf("Resides at %p is %d\n", &v, v);
    return 0;
}