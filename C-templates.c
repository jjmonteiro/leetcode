#include <stdio.h>

// Generic function macro
#define myPrint(var) (func(&var, sizeof(var)))

// Generic function to print an integer or char value
void* func(void* pData, size_t size) {
    if (size == sizeof(int)) {
        int* intPtr = (int*)pData;
        printf("%d\n", *intPtr);
    }
    else if (size == sizeof(char)) {
        char* charPtr = (char*)pData;
        printf("%c\n", *charPtr);
    }
    else
    {
        char* strPtr = (char*)pData;
        printf("%s\n", strPtr);
    }
    return pData;
}

int main()
{
    // Call myPrint for int
    int a = 3;
    myPrint(a);
    // call myPrint for char
    char g = 'g';
    myPrint(g);
    // call myPrint for string
    char s[] = "test";
    myPrint(s);

    return 0;
}