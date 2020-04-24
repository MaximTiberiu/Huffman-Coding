#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/* countChars contorizeaza fiecare caracter prezent in textul supus codarii*/
unsigned int* countChars(char* inputFile)
{
    unsigned int* charArray;  
    charArray = (unsigned int*)calloc(256, sizeof(unsigned int)); /// 256, deoarece in textul din fisierul .in se accepta orice tip de caracter
    assert(charArray != NULL);

    char ch; // variabila in care vom citi, caracter dupa caracter, fisierul .in

    FILE* fin = fopen(inputFile, "r");
    assert(fin != NULL);

    while (1)
    {
        ch = fgetc(fin);
        
        /// verificam daca ch este EOF
        if (ch == EOF) break;
        charArray[ch]++;
    }
    fclose(fin);

    return charArray;
}

/* functia printeaza caracterele numarate intr-un fisier*/
void printCountedChars(unsigned int* charArray, char* outputFile)
{
    FILE* fout;
    fout = fopen(outputFile, "w");
    assert(fout != NULL);

    for (unsigned int i = 0; i < 256; i++)
        if (charArray[i] > 0) // avem caracter de acest tip
        {
            char ch = (char)i;

            /// pentru a o aranjare frumoasa in pagina ne vom scrie "codurile" pentru caracterele speciale

            switch (ch)
            {
            case '\n':
                fprintf(fout, "Caracterul '\\n' : %u\n", charArray[i]);
                break;
            case '\t':
                fprintf(fout, "Caracterul '\\t' : %u\n", charArray[i]);
                break;
            case ' ':
                fprintf(fout, "Caracterul 'space' : %u\n", charArray[i]);
                break;
            default:
                fprintf(fout, "Caracterul '%c' : %u\n", ch, charArray[i]);
                break;
            }
        }
}

/* functia construieste cei doi vectori care vor contine carcaterul si numarul de caractere din text*/
void createCharsFreqArrays(char** chars, unsigned int** freq, unsigned int* charArray)
{
    *chars = (char*)malloc(0 * sizeof(char));
    assert(*chars != NULL);

    *freq = (unsigned int*)malloc(0 * sizeof(unsigned int));
    assert(*freq != NULL);

    unsigned int size = 0; /// cand dam de un nou caracter in vecotorul charArray[], incrementam size

    for(unsigned int i = 0 ; i < 256 ; i++)
        if (charArray[i] > 0)
        {
            size++;

            /// realocam memorie pentru noul caracter gasit
            *chars = (char*)realloc(*chars, size * sizeof(char));
            assert(*chars != NULL);

            *freq = (unsigned int*)realloc(*freq, size * sizeof(unsigned int));
            assert(*freq != NULL);

            /// adaugam caracterul si frecventa acestuia
            (*chars)[size - 1] = (char)i;
            (*freq)[size - 1] = charArray[i];
        }
}

