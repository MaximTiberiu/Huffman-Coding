#pragma once
#include <stdbool.h>

/// structs
/* HuffTreeNode este structura in care memoram caracterul, frecventa acestuia, dar si nodurile copii din arbore, left si right*/
struct HuffTreeNode
{
    char ch;
    unsigned int freq;

    struct HuffTreeNode* left, * right;
};

/* HuffTree este structura in care se memoreaza arborele binar, format din noduri de tip HuffTreeNode*/
struct HuffTree
{
    unsigned int currSize; /// dimensiunea  curenta a arborelui 
    unsigned int totalSize; /// dimensiunea totala a arborelui 

    struct HuffTreeNode** arr; // vector de pointeri catre nodurile din HuffTree; practic, este un minheap
};

/// functions

/*Functia parcurge arborele pentru a gasi codul pentru fiecare caracter*/
void printEncodedChars(char* charArray, unsigned int* freqArray, unsigned int size, char* outputFile);

/*Functia parcurge fisierul .in si afiseaza textul codat*/
void printEncodedText(char* inputFile, char* outputFile, char* charArray, unsigned int* freqArray, unsigned int size);

/*Functia parcurge fisierul de intrare si gaseste caracterul pentru fiecare secventa de text codat*/
void printDecodedText(char* inputFile, char* outputFile, char* charArray, unsigned int* freqArray, unsigned int size);