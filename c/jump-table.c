#include <stdio.h>

// prototypes
static void func1(void);
static void func2(void);
static void func3(void);

typedef struct
{
    int   num;
    char* name;
    void  (*func)(void);
} data_t;

data_t data[] =
{
    { 12, "John", func1},
    { 34, "Bob",  func2},
    { 56, "Anna", func3},
};

static void func1(void) { printf("func1\n"); }
static void func2(void) { printf("func2\n"); }
static void func3(void) { printf("func3\n"); }

int main() {
    int num = 0;

    printf("Search: ");
    (void)scanf("%d", &num);

    for (int i = 0; i < (sizeof(data)/sizeof(data[0])); i++)
    {
        if (data[i].num == num)
        {
            printf("%s\n", data[i].name);
            data[i].func();
            return 0;
        }
    }

    printf("Not found.\n");
    return 0;
}