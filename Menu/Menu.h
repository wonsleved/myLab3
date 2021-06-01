#ifndef MYLAB3_MENU_H
#define MYLAB3_MENU_H
#include <iostream>
#include "../Tree/BinaryTree.h"
#include "../Complex/Complex.h"
#include "../Tree/Heap.h"

void menu();

int getInt();
int getInt(int up);
int getInt(int down, int up);
int getType();
int getDataStruct();
Complex getComplex();
void printComplex(Complex& comp);

//
//          HEAP
//

void heapMenu();


void heapMenuInt(std::vector<Heap<int>*>& intHeap);
void heapMenuDouble(std::vector<Heap<double>*>& doubleHeap);
void heapMenuComplex(std::vector<Heap<Complex>*>& complexHeap);

void heapIntOperations(Heap<int>* heap, std::vector<Heap<int>*>& intHeap);
void heapDoubleOperations(Heap<double>* heap, std::vector<Heap<double>*>& doubleHeap);
void heapComplexOperations(Heap<Complex>* heap, std::vector<Heap<Complex>*>& complexHeap);

//
//          BINARY SEARCH TREE
//

void binaryTreeMenu();

void treeMenuInt(std::vector<BinaryTree<int>*>& intTree);
void treeMenuDouble(std::vector<BinaryTree<double>*>& doubleTree);
void treeMenuComplex(std::vector<BinaryTree<Complex>*>& complexTree);

void treeIntOperations(BinaryTree<int>* tree, std::vector<BinaryTree<int>*>& intTree);
void treeDoubleOperations(BinaryTree<double>* tree, std::vector<BinaryTree<double>*>& doubleTree);
void treeComplexOperations(BinaryTree<Complex>* tree, std::vector<BinaryTree<Complex>*>& complexTree);


#endif
