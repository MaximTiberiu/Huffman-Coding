#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// .h files
#include "data.h"
 
int main()
{
    unsigned int* arr;
    arr = countChars("data.in");
    printCountedChars(arr, "countedChars.out");

    unsigned int* freq;
    char* chars;

    unsigned int size = 0;
    createCharsFreqArrays(&chars, &freq, arr, &size);
    
    HuffmanCoding(chars, freq, size, "codes.out");
    return 0;
}
