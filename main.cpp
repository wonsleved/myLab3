#include <iostream>
#include <fstream>
#include "Tree/BinaryTree.h"

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
    int* a = new int[12] {1, 2, 3, 4, 5, -10, 0, 11, -3, 33, 13, -99};

    BinaryTree<int> test(a, 12);
    test.writeToFile("test.data");
    std::cout << test << std::endl;


    BinaryTree<int> test2;

    test2.insertFromFile("test.data");

    std::cout << test2 << std::endl;

    delete[] a;

    return 0;
}