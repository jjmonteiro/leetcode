#include <iostream>

template <typename T> 
T myMax(T &x, T &y)
{
    if (x > y)
        return (x);
    else
        return (y);
}

template <typename T>
void myPrint(T &x, T &y)
{
    std::cout << myMax(x, y) << std::endl;
}

int main()
{
    // Call myMax for int
    int a = 3;
    int b = 7;
    myPrint(a, b);
    // call myMax for double
    float e = 7.0;
    float f = 3.0;
    myPrint(e, f);
    // call myMax for char
    char g = 'g';
    char h = 'h';
    myPrint(g, h);

    return 0;
}