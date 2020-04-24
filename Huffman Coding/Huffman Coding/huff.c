#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/* HuffTreeNode este structura in care memoram caracterul, frecventa acestuia, dar si nodurile copii din arbore, left si right*/
struct HuffTreeNode
{
    char ch;
    unsigned int freq;

    struct HuffTreeNode *left, *right;
};

/* HuffTree este structura in care se memoreaza arborele binar, care este, de fapt un heap, format din noduri de tip HuffTreeNode*/
struct HuffTree
{
    unsigned int currSize; /// dimensiunea  curenta a arborelui 
    unsigned int totalSize; /// dimensiunea totala a arborelui 

    struct HuffTreeNode** arr; // vector de pointeri catre nodurile din HuffTree
};

/*Functia constuieste un nou nod de tipul HuffTreeNode, pe care il va returna*/
struct HuffTreeNode* createNode(char ch, unsigned int freq)
{
    /// alocam memorie
    struct HuffTreeNode* tempNode = (struct HuffTreeNode*)malloc(sizeof(struct HuffTreeNode));
    assert(tempNode != NULL);

    /// nodul tempNode nu are copii, deci tempNode->left/right = NULL
    tempNode->left = NULL;
    tempNode->right = NULL; 

    /// atribuim caracterul si frecventa acestuia
    tempNode->ch = ch;
    tempNode->freq = freq;

    return tempNode;
}

/*Functia face swap intre doua noduri de tip HuffTreeNode*/
void swapHuffTreeNodes(struct HuffTreeNode** nodeA, struct HuffTreeNode** nodeB)
{
    /// functie utila cand vrem sa rearanjam heapul (heapify)
    struct HuffTreeNode* tempNode = *nodeA;
    *nodeA = *nodeB;
    *nodeB = tempNode;
}

/*Functia construieste arborele de tipul HuffTree, cu o dimeniune totala totalSize*, pe care il va returna*/
struct HuffTree* createTree(unsigned int totalSize)
{
    struct HuffTree* tempTree = (struct HuffTree*)malloc(sizeof(struct HuffTree));
    assert(tempTree != NULL);

    tempTree->currSize = 0; /// dimensiunea curenta este 0, pentru ca nu avem niciun nod adaugat
    tempTree->totalSize = totalSize;

    /// alocam memorie pentru cele totalSize noduri de tipul HuffTreeNode
    tempTree->arr = (struct HuffTreeNode**)malloc(totalSize * sizeof(struct HuffTreeNode*));
    assert(tempTree->arr != NULL);

    return tempTree;
}

/*Functia constuieste un heap in subarborele cu radacina in nodul i*/
void Heapify(struct HuffTree* huffTree, unsigned int i)
{
    /// heapul nostru este practic un minheap, deci avem nevoie de valoarea cea mai mica
    /// valoarea cea mai mica este frecventa cea mai mica in cazul acesta, deci comparam elementul freq din struct

    unsigned int smallestNode = i; /// consideram nodul i ca fiind cel mai mic nod
    
    /// calculam pozitia nodurilor copiilor nodului i
    unsigned int leftNode = 2 * i + 1;
    unsigned int rightNode = 2 * i + 2;

    if (leftNode < huffTree->currSize)
    {
        /// daca nodul din stanga exista
        if (huffTree->arr[leftNode]->freq < huffTree->arr[i]->freq)
            smallestNode = leftNode;
    }

    if (rightNode < huffTree->currSize)
    {
        /// daca nodul din exista
        if (huffTree->arr[rightNode]->freq < huffTree->arr[i]->freq)
            smallestNode = rightNode;
    }

    if (smallestNode != i)
    {
        /// daca smallestNode era unul dintre copii, si nu nodul radacina, atunci facem swap
        swapHuffTreeNodes(&huffTree->arr[smallestNode], &huffTree->arr[i]);
        Heapify(huffTree, smallestNode); /// continuam procedura recursiv, pana cand nu mai exista schimbari
    }
}

/*Functia insereaza un nou nod in arborele binar*/
void insertNodetoTree(struct HuffTreeNode* newNode, struct HuffTree* huffTree)
{
    /// .....
}
