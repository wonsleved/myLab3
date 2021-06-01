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

void heapMenuInt(std::vector<Heap<int>*>& intHeap);

#endif
