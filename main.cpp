#include <iostream>
#include "Tree/BinaryTree.h"



int main() {
    int* a = new int[8] {3, 2, 1, 4, 5, -10, 0, 11};
    try {

        BinaryTree<int> test(a, 5);
        std::cout << test << std::endl;
        test.remove(3);
        std::cout << test << std::endl;
        test.insert(3);
        std::cout << test << std::endl;

    } catch(Exceptions& Exception) {
        Exception.getError();
    }

    delete[] a;

    return 0;
}