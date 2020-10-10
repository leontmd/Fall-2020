#include <stdio.h>

int main()
{
    int ROW = 10;
    int COL = 10;

    int a[ROW][COL];

    int value = 0;

    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            a[i][j] = value++;
        }
    }

    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    // int ans = ((int*)a)[47];

    printf("%d\n", a[11][-15]);

    return 0;
}