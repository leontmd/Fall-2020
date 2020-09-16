#include <stdio.h>

int main()
{
    int x = 1000000000;
    int y = 2000000000;
    int z = x + y;
    printf("%d\n", z); //maybe -1294967296

    //No unsigned int overflow
    unsigned int u_x = 1000000000;
    unsigned int u_y = 2000000000;
    unsigned int u_z = u_x + u_y; //Definitely 3000000000
    printf("%u\n", z);

    return 0;
}