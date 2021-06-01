#ifndef MYLAB3_HEAP_H
#define MYLAB3_HEAP_H



#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <functional>
#include "../Exceptions/Exceptions.h"

using std::vector;
using std::string;
using std::cout;

template <class T>
class Heap
{
private:
    T* m_data;
    int m_size;
public:
    Heap();
    Heap(T& item);
    Heap(T&& item);
    Heap(T* items, int count);
    Heap(Heap& another);

    ~Heap();




    Heap<T>& insert(T& item);
    Heap<T>& insert(T&& item);

    Heap<T>& remove(T& item);
    Heap<T>& remove(T&& item);

    bool searchItem(T& item);
    bool searchItem(T&& item);

    Heap<T>* cut(T& item);
    Heap<T>* cut(T&& item);

    bool searchSubHeap(Heap<T>& another);
    bool searchSubHeap(Heap<T>&& another);

    void print();
    int getSize();

private:
    void quickSort(T* array, int low, int high);
    int getHeight(int index);
    int getRightChild(int index);
    int getLeftChild(int index);
    int getParent(int index);
    Heap<T>& preOrderTravers(int index, std::function<void(T*)> func);
    bool searchSubHeapDev(Heap<T>& another);
};




#include "Heap.inl"


#endif
