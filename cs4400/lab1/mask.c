#include "stdio.h"

/**
 *  BIG ENDIAN AND LITTLE ENDIAN
 *  Suppose we have 0x12345678 stored at 0x00400000
 *  The most significant byte is 0x12
 *  The least significant byte is 0x78
 * 
 *  Big Endian: 12 -> 00400000
 *              34 -> 00400001
 *              56 -> 00400002
 *              78 -> 00400003
 * 
 *  Little Endian:  78 -> 00400000
 *                  56 -> 00400001
 *                  34 -> 00400002
 *                  12 -> 00400003
 */

int main()
{
    //  The most significant byte is AA
    //  The least significant byte is DD
    //  1010 1010 1011 1011 1100 1100 1101 1101
    unsigned int bits = 0xAABBCCDD;
    printf("%d\n", bits);

    unsigned char MSB = bits >> 24;
    printf("%x\n", MSB);
    printf("%d\n", MSB);
    
    //  Extract bits 20 through 25 (by index, starts with 0)
    //  0010 1011 (0x2B)
    //  A char is 8 bits, so it also contains unnecessary bits 1 and 0
    unsigned char shifted = bits >> 20;
    //  ab      --> 1010 1011, we want 00101011
    printf("%x\n", shifted);
    //  171
    printf("%d\n", shifted);

    // mask = 0011 1111
    unsigned char mask = 0x3F;
    shifted = shifted & mask;
    //  2B
    printf("%x\n", shifted);
    //  43
    printf("%d\n", shifted);


    // little endian if true
    // This machine is little endian
    int n = 1;
    if(*(char *)&n == 1) {printf("little endian");}
    else
    {
        printf("big endian");
    }
    
    return 0;
}