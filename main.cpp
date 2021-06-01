#include <iostream>
#include <fstream>
#include "Tree/BinaryTree.h"
#include "./Complex/Complex.h"
#include "./Tree/Heap.h"
#include "./Menu/Menu.h"

int mop(const int& item) {
    return item+1;
}
bool filt(const int& item) {
    return item%2;
}

int red(const int& prev, const int& cur) {
    return prev + cur;
}

int main() {

    int* a = new int[12] {1, 2, 3, 5, -10, 0, 11, -3, 33, 13, -99, 7};
    Heap<int> test(a, 12);
    std::cout << test << std::endl;
    test.writeToFile("heap.data");
    Heap<int> test2(101);
    test2.insertFromFile("heap.data");

    std::cout << test2 << std::endl;




    delete[] a;
    return 0;
}