#include "Tests.h"

void BinaryTreeIntTest() {
    std::cout << std::endl <<"\t\t\t\t\t\t\t\tBinary search tree test INT" << std::endl;
    BinaryTree<int> test(-1);

    std::cout << "|0%";
    for (int i = 2; i < 95; i++)
        std::cout << " ";
    std::cout << "100%|" << std::endl;

    std::cout << "[\x1B[92m";
    for (int i = 0; i < 10000; i++) {
        test.insert(i);
        assert(test.searchItem(i));
        test.remove(i);
        assert(!test.searchItem(i));
        if (!(i % 100))
            std::cout << "#";
    }
    std::cout << "\033[0m]" << std::endl;
}

void BinaryTreeDoubleTest() {
    std::cout << std::endl <<"\t\t\t\t\t\t\t\tBinary search tree test DOUBLE" << std::endl;
    BinaryTree<double> test(-1.1);

    std::cout << "|0%";
    for (int i = 2; i < 95; i++)
        std::cout << " ";
    std::cout << "100%|" << std::endl;

    std::cout << "[\x1B[92m";
    for (int i = 0; i < 10000; i++) {
        test.insert(i + 0.1);
        assert(test.searchItem(i + 0.1));
        test.remove(i + 0.1);
        assert(!test.searchItem(i + 0.1));
        if (!(i % 100))
            std::cout << "#";
    }
    std::cout << "\033[0m]" << std::endl;
}

void BinaryTreeComplexTest() {
    std::cout << std::endl <<"\t\t\t\t\t\t\t\tBinary search tree test COMPLEX" << std::endl;
    Complex comp(-1, -1);
    BinaryTree<Complex> test(comp);

    std::cout << "|0%";
    for (int i = 2; i < 95; i++)
        std::cout << " ";
    std::cout << "100%|" << std::endl;

    std::cout << "[\x1B[92m";
    for (int i = 0; i < 10000; i++) {
        comp.setReal(i);
        comp.setImage(i);
        test.insert(comp);
        assert(test.searchItem(comp));
        test.remove(comp);
        assert(!test.searchItem(comp));
        if (!(i % 100))
            std::cout << "#";
    }
    std::cout << "\033[0m]" << std::endl;
}



void HeapTreeIntTest() {
    std::cout << std::endl <<"\t\t\t\t\t\t\t\t\t\tHeap test INT" << std::endl;
    Heap<int> test(-1);

    std::cout << "|0%";
    for (int i = 2; i < 95; i++)
        std::cout << " ";
    std::cout << "100%|" << std::endl;

    std::cout << "[\x1B[92m";
    for (int i = 0; i < 10000; i++) {
        test.insert(i);
        assert(test.searchItem(i));
        test.remove(i);
        assert(!test.searchItem(i));
        if (!(i % 100))
            std::cout << "#";
    }
    std::cout << "\033[0m]" << std::endl;
}

void HeapTreeDoubleTest() {
    std::cout << std::endl <<"\t\t\t\t\t\t\t\t\t\tHeap test DOUBLE" << std::endl;
    Heap<double> test(-1.1);

    std::cout << "|0%";
    for (int i = 2; i < 95; i++)
        std::cout << " ";
    std::cout << "100%|" << std::endl;

    std::cout << "[\x1B[92m";
    for (int i = 0; i < 10000; i++) {
        test.insert(i + 0.1);
        assert(test.searchItem(i + 0.1));
        test.remove(i + 0.1);
        assert(!test.searchItem(i + 0.1));
        if (!(i % 100))
            std::cout << "#";
    }
    std::cout << "\033[0m]" << std::endl;
}

void HeapTreeComplexTest() {
    std::cout << std::endl <<"\t\t\t\t\t\t\t\t\t\tHeap test COMPLEX" << std::endl;
    Complex comp(-1, -1);
    Heap<Complex> test(comp);

    std::cout << "|0%";
    for (int i = 2; i < 95; i++)
        std::cout << " ";
    std::cout << "100%|" << std::endl;

    std::cout << "[\x1B[92m";
    for (int i = 0; i < 10000; i++) {
        comp.setReal(i);
        comp.setImage(i);
        test.insert(comp);
        assert(test.searchItem(comp));
        test.remove(comp);
        assert(!test.searchItem(comp));
        if (!(i % 100))
            std::cout << "#";
    }
    std::cout << "\033[0m]" << std::endl;
}