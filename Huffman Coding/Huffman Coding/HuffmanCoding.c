#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// .h files
#include "data.h"
#include "huff.h"
#include "encode_decode.h"
 
int main()
{
    unsigned int* arr;
    arr = countChars("data.in");
    printCountedChars(arr, "countedChars.out");

    unsigned int* freq;
    char* chars;

    unsigned int size = 0;
    createCharsFreqArrays(&chars, &freq, arr, &size);
    
    printEncodedChars(chars, freq, size, "codes.out");

    //printEncodedText("data.in", "encodedText.out", chars, freq, size);

    FILE* fout = fopen("encodedText.out", "w");
    bool* printArr = (bool*)malloc(50 * sizeof(bool));
    struct HuffTreeNode* root = buildHuffTreeFindRoot(chars, freq, size);

    unsigned int i = 0;
    getCharCode(root, 'a', printArr, &i, fout);
    fclose(fout);
    return 0;
}
