#include <stdio.h>

typedef struct node
{
    short x;
    int y;
    double z;
    struct node* next;
}node;

typedef struct mystruct
{
    char a;
    char b[12];
    int c;
    int d[2];
}mystruct;

int main()
{
    // node n;
    // printf("%ld\n", (char*)&n.next - (char*) &n);   

    mystruct str;
    printf("%ld\n", (char*)&str.d - (char*)&str);
    return 0;
}