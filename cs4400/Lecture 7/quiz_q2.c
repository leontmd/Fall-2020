#include <stdio.h>

struct student
{
    char name[50];
    int uid;
    float gpa;
};

struct student top_4400_student={"Jane Doe", 1234567, 4.0};

typedef struct student student;

void incr_gpa(student a, student* b)
{
    a.gpa += 0.1;
    b->gpa += 0.1;
}

int main()
{
    student s = {"Jane Doe", 1234567, 4.0};
    student t = {"John Doe", 7654321, 3.4};

    incr_gpa(s, &t);
    printf("%.1f", s.gpa);
    printf("%.1f", t.gpa);
}