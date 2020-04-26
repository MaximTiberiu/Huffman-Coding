#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// .h files
#include "data.h"
#include "huff.h"
 
int main()
{
    if (isFileEmpty("data.in"))
    {
        printf("Fisierul este gol! Te rog completeaza fisierul!...\n");
        return 0;
    }
    else
    {
        unsigned int* freqCharsArray;
        freqCharsArray = countChars("data.in");
        printCountedChars(freqCharsArray, "countedChars.out");

        unsigned int* freqArray;
        char* charArray;

        unsigned int size = 0;
        createCharsFreqArrays(&charArray, &freqArray, freqCharsArray, &size);
        free(freqCharsArray);

        printEncodedChars(charArray, freqArray, size, "codes.out");

        printEncodedText("data.in", "encodedText.out", charArray, freqArray, size);
        printDecodedText("encodedText.out", "decodedText.out", charArray, freqArray, size);

        free(charArray);
        free(freqArray);

        printf("Codarea Huffman a fost realizata cu succes!\nVerifica urmatoarele fisiere:\n");
        printf("\t-'countedChars.out', pentru frecventa caracterelor;\n");
        printf("\t-'codes.out', pentru codurile caracterelor;\n");
        printf("\t-'encodedText.out', pentru textul codat;\n");
        printf("\t-'decodedText.out', pentru textul decodat.\n\n\n\n\n");
        return 0;
    }
}
