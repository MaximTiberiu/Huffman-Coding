#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*Functie care verifica daca fisierul .in este gol*/
bool isFileEmpty(char* inputFile)
{
    FILE* fin = fopen(inputFile, "r");

    char ch = fgetc(fin);
    fclose(fin);
    bool ret;
    
    if (ch != EOF) ret = false; // fisierul nu este gol
    ret = true; /// fisierul este gol

    return ret;
}

/* countChars contorizeaza fiecare caracter prezent in textul supus codarii*/
unsigned int* countChars(char* inputFile)
{
    unsigned int* freqCharsArray;  
    freqCharsArray = (unsigned int*)calloc(256, sizeof(unsigned int)); /// 256, deoarece in textul din fisierul .in se accepta orice tip de caracter
    assert(freqCharsArray != NULL);

    char ch; // variabila in care vom citi, caracter dupa caracter, fisierul .in

    FILE* fin = fopen(inputFile, "r");
    assert(fin != NULL);

    while (1) // parcurgem intreg fisierul
    {
        ch = fgetc(fin);
        
        /// verificam daca ch este EOF
        if (ch == EOF) break;

        freqCharsArray[ch]++; // incrementam
    }
    fclose(fin);

    return freqCharsArray;
}

/* functia printeaza caracterele numarate intr-un fisier*/
void printCountedChars(unsigned int* freqCharsArray, char* outputFile)
{
    FILE* fout;
    fout = fopen(outputFile, "w");
    assert(fout != NULL);

    for (unsigned int i = 0; i < 256; i++)
        if (freqCharsArray[i] > 0) // avem caracter de acest tip
        {
            char ch = (char)i;

            /// pentru a o aranjare frumoasa in pagina ne vom scrie "codurile" pentru caracterele speciale

            switch (ch)
            {
            case '\n':
                fprintf(fout, "\\n : %u\n", freqCharsArray[i]);
                break;
            case '\t':
                fprintf(fout, "\\t : %u\n", freqCharsArray[i]);
                break;
            case ' ':
                fprintf(fout, "space : %u\n", freqCharsArray[i]);
                break;
            default:
                fprintf(fout, "%c : %u\n", ch, freqCharsArray[i]);
                break;
            }
        }
    fclose(fout);
}

/* Functia construieste cei doi vectori care vor contine caracterul si nummarul de aparitii ale caracterului din text*/
void createCharsFreqArrays(char** charArray, unsigned int** freqArray, unsigned int* freqCharsArray, unsigned int* size)
{
    *charArray = (char*)malloc(0 * sizeof(char));
    assert(*charArray != NULL);

    *freqArray = (unsigned int*)malloc(0 * sizeof(unsigned int));
    assert(*freqArray != NULL);


    for(unsigned int i = 0 ; i < 256 ; i++)
        if (freqCharsArray[i] > 0)
        {
            (*size)++; /// cand dam de un nou caracter in vecotorul charArray[], incrementam size

            /// realocam memorie pentru noul caracter gasit
            *charArray = (char*)realloc(*charArray, *size * sizeof(char));
            assert(*charArray != NULL);

            *freqArray = (unsigned int*)realloc(*freqArray, *size * sizeof(unsigned int));
            assert(*freqArray != NULL);

            /// adaugam caracterul si frecventa acestuia
            (*charArray)[(*size) - 1] = (char)i;
            (*freqArray)[(*size) - 1] = freqCharsArray[i];
        }
}