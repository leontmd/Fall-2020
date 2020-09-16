
//gcc -S -Og mulstore.c -> multstore.s
//gcc -c mulstore.s -> mulstore.o

long mult2(long a, long b);

void multstore(long x, long y, long* dest)
{
    long t = mult2(x, y);
    *dest = t;
}