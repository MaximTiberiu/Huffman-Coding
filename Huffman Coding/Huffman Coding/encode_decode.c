#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

// .h files
#include "huff.h"


/*Functia afiseaza codurile pentru fiecare caracter*/
void getCharCode(struct HuffTreeNode* root, char ch, bool* printArr, unsigned int* currSize, FILE* fout)
{
    if (root->left)
    {
        printArr[*currSize] = 0; /// pentru partea stanga a arborelui asignam valoarea 0;
        getCharCode(root->left, ch, printArr, *currSize + 1, fout); /// apelam recursiv
    }

    if (root->left)
    {
        printArr[*currSize] = 1; /// pentru partea dreapta a arborelui asignam valoarea 0;
        getCharCode(root->right, ch, printArr, *currSize + 1, fout); /// apelam recursiv
    }

    if (isLeaf(root) == true && root->ch == ch) // am gasit caracterul ch in arbore, printam printArr[]
    {
        for (unsigned int i = 0; i < *currSize; i++)
            fprintf(fout, "%d", printArr[i]);
    }
    else printf("NU");
            
}

void printEncodedText(char* inputFile, char* outputFile, char* charArray, unsigned int* freqArray, unsigned int size)
{
    struct HuffTreeNode* root = buildHuffTreeFindRoot(charArray, freqArray, size);

    bool* printArr = (bool*)malloc((size / 2) * sizeof(bool)); // printArr este vectorul in care memoram codul de pe fiecare nivel; 
                                                               // (size / 2) - numar maxim de nivele ale arborelui
    assert(printArr != NULL);

    FILE* fin = fopen(inputFile, "r");
    assert(fin != NULL);

    FILE* fout = fopen(outputFile, "w");
    assert(fout != NULL);

    unsigned int fileLength = 0;

    char ch;
    while (1)
    {
        ch = fgetc(fin);

        /// verificam daca ch este EOF
        if (ch == EOF) break;
        
        /// printam codul
        unsigned int codeSize = 0;
        getCharCode(root, ch, printArr, &codeSize, fout);
        
        fileLength += codeSize;

        if (fileLength > 30)
        {
            fprintf(fout, "\n");
            fileLength = 0;
        }
    }

    fclose(fin);
    fclose(fout);
}
