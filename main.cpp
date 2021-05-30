#include <iostream>
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
    int* a = new int[8] {3, 2, 1, 4, 5, -10, 0, 11};
    try {
        BinaryTree<int> test(a, 8);

        std::cout << test << std::endl;

        int aa = 2;
        BinaryTree<int>* s = test.cutTree(aa);

        std::cout << *s << std::endl;


        delete s;
    } catch(Exceptions& Exception) {
        Exception.getError();
    }

    delete[] a;

    return 0;
}