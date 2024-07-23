#include <stdio.h>

// Can change the pointer but not the data
void modData1(const char* pData) {
    pData = "Goodbye, world!";
    printf("%s\n", pData); // Print the new string that pData points to
}

// Can change the data, but not the pointer
void modData2(char* const pData) {
    *pData = 'X'; // Modify the first character of the string
    printf("%s\n", pData); // Print the modified string
}

int main() {
    char myString[] = "Hello, world!"; // Original string
    printf("%s\n", myString); // Print the original string

    modData1(myString); // Print the new string "Goodbye, world!"

    modData2(myString); // Print the modified string "Xello, world!"

    return 0;
}
