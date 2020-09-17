// Lab 1 - hello.c

#include <stdio.h>

main()
{
    unsigned int bits = 0xAABBCCDD;
    unsigned char MSB = bits >> 24;
    unsigned char shifted = bits >> 20;
    unsigned char mask = 0x3f;
    printf("%x\n", shifted & 0x3f);
    
    unsigned short twoMostSigBytes = bits >> 24;
    printf("%x\n", twoMostSigBytes);
    unsigned char twoLeastSigBits = bits << 30;
    printf("%x\n", twoLeastSigBits);
    unsigned char bitsSevenToNine = (bits >> 7) & 0x01;
    printf("%x\n", bitsSevenToNine);

    short questionten = 0xAAAA;
    int varible = (int)questionten;
    printf("%d\n", varible);
}
