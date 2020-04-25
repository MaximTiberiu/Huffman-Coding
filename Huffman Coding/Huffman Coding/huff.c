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

/* HuffTree este structura in care se memoreaza arborele binar, format din noduri de tip HuffTreeNode*/
struct HuffTree
{
    unsigned int currSize; /// dimensiunea  curenta a arborelui 
    unsigned int totalSize; /// dimensiunea totala a arborelui 

    struct HuffTreeNode** arr; // vector de pointeri catre nodurile din HuffTree; practic, este un minheap
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

/*Functia rearanjeaza nodurile astfel incat sa respecte conditia de heap in subarborele cu radacina in nodul i*/
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
        Heapify(huffTree, smallestNode); /// continuam procedura recursiv, in subarborele afectat, pana cand nu mai exista schimbari
    }
}

/*Functia insereaza un nou nod in arborele binar*/
void insertNodetoTree(struct HuffTreeNode* newNode, struct HuffTree* huffTree)
{
    /// incrementam dimensiunea curenta
    huffTree->currSize++;

    /// vom introduce noul nod la pozitia currSize - 1
    huffTree->arr[huffTree->currSize - 1] = newNode;

    /// rearanjam minheap-ul
    Heapify(huffTree, 0);
}

/*Functia extrage cel mai mic nod, cel cu frecventa minima*/
struct HuffTreeNode* getMinNode(struct HuffTree* huffTree)
{
    struct HuffTreeNode* tempNode = huffTree->arr[0]; /// cel mai mic nod este chiar primul element al heap-ului

    /// inlocuim primul element cu ultimul
    huffTree->arr[0] = huffTree->arr[huffTree->currSize - 1];

    /// decrementam dimeniunea curenta
    huffTree->currSize--;

    /// rearanjam heap-ul, pornind de la primul nod
    Heapify(huffTree, 0);

    return tempNode;
}

/*Functia verifica daca nodul este frunza*/
bool isLeaf(struct HuffTreeNode* node)
{
    if (node->left == NULL && node->right == NULL) return true;
    return false;
}

/*Functia apeleaza Heapify() pentru intreg arborele*/
void buildTreeHeap(struct HuffTree* huffTree)
{
    for (int i = huffTree->currSize - 1 ; i >= 0; i--)
        Heapify(huffTree, i);
}

/*Functia construieste heapul din structura HuffTree, cu datele din vectorii charArray si freqArray*/
struct HuffTree* createHuffTree(char* charArray, unsigned int* freqArray, unsigned int size)
{
    struct HuffTree* huffTree = createTree(size); /// alocam memorie pentru arbore

    /// completam huffTree->arr[]

    for (unsigned int i = 0; i < size; i++)
        huffTree->arr[i] = createNode(charArray[i], freqArray[i]);

    huffTree->currSize = size; /// atribuim dimensiunea curenta

    /// apelam Heapify() pe intreg arborele, pentru a forma minheap-ul

    for (int i = huffTree->currSize - 1; i >= 0; i--)
        Heapify(huffTree, i);

    return huffTree;
}

/*Functia construieste arborele iar, la final, returneaza nodul radacina*/
struct HuffTreeNode* buildHuffTreeFindRoot(char* charArray, unsigned int* freqArray, unsigned int size)
{
    struct HuffTreeNode *left, *right, *mid, *root;
    struct HuffTree* huffTree = createHuffTree(charArray, freqArray, size); /// completam heapul

    while (huffTree->currSize > 1)
    {
        /// extragem primele doua noduri din heap
        left = getMinNode(huffTree);
        right = getMinNode(huffTree);

        /// nodul intermediar mid va avea valorile \0, pentru char, iar la frecventa va avea suma celor doua noduri minime
        mid = createNode('\0', left->freq + right->freq);

        /// formam legaturile
        mid->left = left;
        mid->right = right;

        /// inseram nodul mid in arbore
        insertNodetoTree(mid, huffTree);
    }

    /// currSize a devenit 1, deci nodul ramas este radicina si il extragem
    root = getMinNode(huffTree);

    return root;
}

/*Functia afiseaza codurile pentru fiecare caracter*/
void printCodes(struct HuffTreeNode* root, bool* printArr, unsigned int currSize, FILE* fout)
{
    if (root->left)
    {
        printArr[currSize] = 0; /// pentru partea stanga a arborelui asignam valoarea 0;
        printCodes(root->left, printArr, currSize + 1, fout); /// apelam recursiv
    }

    if (root->left)
    {
        printArr[currSize] = 1; /// pentru partea dreapta a arborelui asignam valoarea 0;
        printCodes(root->right, printArr, currSize + 1, fout); /// apelam recursiv
    }

    if (isLeaf(root) == true)
    {
        switch (root->ch)
        {
            case '\n':
                fprintf(fout, "\\n : ");
                break;
            case '\t':
                fprintf(fout, "\\t : ");
                break;
            case ' ':
                fprintf(fout, "space : ");
                break;
            default:
                fprintf(fout, "%c : ", root->ch);
                break;
        }

        /// printam codul
        for (unsigned int i = 0; i < currSize; i++)
            fprintf(fout, "%d", printArr[i]);

       fprintf(fout, "\n");
    }
}

void printEncodedChars(char* charArray, unsigned int* freqArray, unsigned int size, char* outputFile)
{
    struct HuffTreeNode* root = buildHuffTreeFindRoot(charArray, freqArray, size);

    bool* printArr = (bool*)malloc((size / 2) * sizeof(bool)); // printArr este vectorul in care memoram codul de pe fiecare nivel; 
                                                               // (size / 2) - numar maxim de nivele ale arborelui
    assert(printArr != NULL);

    FILE* fout = fopen(outputFile, "w");
    assert(fout != NULL);

    printCodes(root, printArr, 0, fout);
    fclose(fout);
}