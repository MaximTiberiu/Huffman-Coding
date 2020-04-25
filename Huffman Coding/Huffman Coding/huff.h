#pragma once

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
void printEncodedChars(char*, unsigned int*, unsigned int, char*);