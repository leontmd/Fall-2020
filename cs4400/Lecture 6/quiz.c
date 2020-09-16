#include <stdio.h>

void update(int arr[2]) {
  arr[4]++;
}

int main()
{
    //  QUESTION 1
    // short arr[] = { 2, 4, 6, 8, 10, 12, 14, 16 };
    // short* p1 = arr + 10;
    // short* p2 = arr + 6;

    // short answer = *(arr + (p1 - p2));

    // printf("%d\n", answer);


    //  QUESTION 2
    int x[] = { 0, 0, 0, 0, 0 };
    update(x);
    printf("%d,%d\n", x[2], x[4]);
    return 0;
}