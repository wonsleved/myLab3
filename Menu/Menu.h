#ifndef MYLAB3_MENU_H
#define MYLAB3_MENU_H
#include <iostream>
#include "../Tree/BinaryTree.h"
#include "../Complex/Complex.h"
#include "../Tree/Heap.h"
//void menuFloat();
//void menuComplex();
//void PrintMenu();
void menu();

void heapMenu();
void binaryTreeMenu();

int getInt();
int getInt(int up);
int getInt(int down, int up);
int getType();

int getDataStruct();

Complex getComplex();
void printComplex(Complex& comp);

void heapMenuInt(std::vector<Heap<int>*>& intHeap);
void heapMenuDouble(std::vector<Heap<double>*>& doubleHeap);
void heapMenuComplex(std::vector<Heap<Complex>*>& complexHeap);





void heapIntOperations(Heap<int>* heap, std::vector<Heap<int>*>& intHeap);
void heapDoubleOperations(Heap<double>* heap, std::vector<Heap<double>*>& doubleHeap);
void heapComplexOperations(Heap<Complex>* heap, std::vector<Heap<Complex>*>& complexHeap);




#endif
