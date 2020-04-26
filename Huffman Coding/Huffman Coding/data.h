#pragma once
#include <stdbool.h>

/* countChars contorizeaza fiecare caracter prezent in textul supus codarii*/
unsigned int* countChars(char* inputFile);

/* Functia printeaza caracterele numarate intr-un fisier*/
void printCountedChars(unsigned int* charArray, char* outputFile);

/* Functia construieste cei doi vectori care vor contine caracterul si nummarul de aparitii ale caracterului din text*/
void createCharsFreqArrays(char** charArray, unsigned int** freqArray, unsigned int* freqCharsArray, unsigned int* size);

/*Functie care verifica daca fisierul .in este gol*/
bool isFileEmpty(char* inputFile);