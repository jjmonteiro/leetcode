#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
    int a;
    int b;
    int c;
};

typedef struct triangle triangle;

void swap(triangle* t1, triangle* t2) {
    triangle temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

float calc_area(triangle* tr)
{
    float p, s;
    p = ((tr->a + tr->b + tr->c) / 2.0f);
    s = sqrt(p * (p - tr->a) * (p - tr->b) * (p - tr->c));
    return s;
}

void sort_by_area(triangle* tr, int n)
{
    for (int a = 0; a < n; a++) {
        for (int i = 0; i < n - 1; i++) 
        {
            float this_area = calc_area(&tr[i]);
            float next_area = calc_area(&tr[i+1]);

            if (next_area < this_area) {
                swap(&tr[i], &tr[i + 1]);
            }
        }
    }
}

int main()
{
    int n = 3;

    triangle tr[] =
    {
        {7, 24, 25},//84
        {5, 12, 13},//30
        {3, 4, 5},//6
    };

    sort_by_area(tr, n);

    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
    }
    return 0;
}