#include <stdio.h>
#include <stdbool.h>

bool isPresent(int n, int A[], int N)
{
    for (int i = 0; i < N; i++)
        if (A[i] == n)
            return true;
    return false;
}

int main() {
    int A[] = {-1, 0, 2, 3}; // should be 1
    int len = (sizeof(A)/sizeof(A[0]));
    int res = 1;
    
    for (int i = 0; i < len; i++)
    {
        if ((isPresent(i, A, len) == false) && (i > 0))
        {
            res = i;
            break;
        }
    }

    printf("The result is %d\n", res);
    return 0;
}