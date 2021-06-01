#include <iostream>
#include <fstream>
#include "Tree/BinaryTree.h"
#include "./Complex/Complex.h"
#include "./Tree/Heap.h"
#include "./Menu/Menu.h"


int main() {

    try {
        menu();
    } catch (Exceptions& exception) {
        exception.getError();
    }

    return 0;
}