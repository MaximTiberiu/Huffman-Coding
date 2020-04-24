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

    createCharsFreqArrays(&chars, &freq, arr);
    printf("%c %u", chars[1], freq[1]);
    return 0;
}
