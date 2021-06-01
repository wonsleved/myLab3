#include "Menu.h"

Complex getComplex() {
    int real;
    std::cout << "\n\t\t\treal: ";
    std::cin >> real;
    int image;
    std::cout << "\t\t\timage: ";
    std::cin >> image;
    return Complex(real, image);
}

//void printComplex(Heap<Complex>* comp) {
//    std::cout << comp->getReal();
//    if (comp->getImage() > 0)
//        std::cout << "+";
//    std::cout << comp->getImage() << "i" << std::endl;
//}

int getInt() {
    int a;
    std::cin >> a;
    return a;
}

int getInt(int up) {
    int a;
    std::cin >> a;
    if (a > up) {
        std::cout << "There is no this option. Try again.\n";
        return getInt(up);
    }
    return a;
}

int getInt(int down, int up) {
    int a;
    std::cin >> a;
    if (a > up || a < down) {
        std::cout << "There is no this option. Try again.\n";
        return getInt(down, up);
    }
    return a;
}

int getType() {
    std::cout << "\tChoose data type: \n"
              << "\t\t1| Int\n"
              << "\t\t2| Double\n"
              << "\t\t3| Complex\n"
              << "\t\t0| exit\n"
              << "\t\t: ";
    return getInt(0, 3);
}

int getDataStruct() {
    std::cout << "\tChoose data structure: \n"
              << "\t\t1| Heap\n"
              << "\t\t2| Binary search tree\n"
              << "\t\t0| exit\n"
              << "\t\t: ";
    return getInt(0, 2);
}


void menu() {
    while (true) {
        int choice = getDataStruct();
        switch (choice) {
            case (1): {
                heapMenu();
                break;
            }
            case (2): {
//                binaryTreeMenu();
                break;
            }
            default:
                return;
        }
    }
}

void heapMenu() {
    std::vector<Heap<int>*> intHeap;
    std::vector<Heap<double>*> doubleHeap;
    std::vector<Heap<Complex>*> complexHeap;

    bool flag = true;

    while (flag) {
        int type = getType();
        switch (type) {
            case (1): {
                heapMenuInt(intHeap);
                break;
            }
            case (2): {
                heapMenuDouble(doubleHeap);
                break;
            }
            case (3): {
                heapMenuComplex(complexHeap);
                break;
            }
            default:
                flag = false;
                break;
        }
    }
    for(auto& heap : intHeap)
        delete heap;
    for(auto& heap : doubleHeap)
        delete heap;
    for(auto& heap : complexHeap)
        delete heap;
}

void heapMenuInt(std::vector<Heap<int>*>& intHeap) {
    while(true) {
        std::cout << "\tChoose option:\n"
                  << "\t\t1| Add heap\n"
                  << "\t\t2| Choose operation\n"
                  << "\t\t3| Print heaps\n"
                  << "\t\t4| Tests\n"
                  << "\t\t5| Delete\n"
                  << "\t\t0| exit\n"
                  << "\t\t: ";
        int choice = getInt(0, 5);
        switch (choice) {
            case (1): {
                int num;
                std::cout << "\t\tEnter number of elements: ";
                std::cin >> num;
                int* arr = new int[num];

                for (int i = 0; i < num; i++) {
                    std::cout << "\t\tEnter [" << i << "] element: ";
                    std::cin >> arr[i];
                }
                Heap<int>* tmp = new Heap(arr, num);
                intHeap.emplace_back(tmp);
                std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                delete[] arr;
                break;
            }
            case (2): {
                if (!intHeap.size()) {
                    std::cout << "\t\t\x1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << intHeap.size()
                          << " heaps. Choose the index of heap to print"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, intHeap.size() - 1);

                heapIntOperations(intHeap.at(index), intHeap);

                break;
            }
            case (3): {
                if (!intHeap.size()) {
                    std::cout << "\t\t\x1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << intHeap.size()
                << " heaps. Choose the index of heap to print"
                << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, intHeap.size() - 1);

                std::cout << *(intHeap[index]) << std::endl;

                break;
            }
            case (4): {
                // ... Tests
                break;
            }
            case (5): {
                if (!intHeap.size()) {
                    std::cout << "\tx1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << intHeap.size()
                          << " heaps. Choose the index of heap to delete"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, intHeap.size() - 1);
                std::cout << "\t\x1B[91mDelete\033[0m " << index << " \x1B[91mheap?\033[0m" << std::endl;
                std::cout << "\t\t1| Yes\n"
                          << "\t\t0| No\n";
                std::cout << "\t\t: ";
                int lastChoice = getInt(0, 1);
                if (lastChoice) {
                    delete intHeap.at(index);
                    intHeap.erase(intHeap.begin() + index);
                    std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                }
                break;
            }
            default:
                return;
        }




        break;
    }
}

void heapMenuDouble(std::vector<Heap<double>*>& doubleHeap) {
    while(true) {
        std::cout << "\tChoose option:\n"
                  << "\t\t1| Add heap\n"
                  << "\t\t2| Choose operation\n"
                  << "\t\t3| Print heaps\n"
                  << "\t\t4| Tests\n"
                  << "\t\t5| Delete\n"
                  << "\t\t0| exit\n"
                  << "\t\t: ";
        int choice = getInt(0, 5);
        switch (choice) {
            case (1): {
                int num;
                std::cout << "\t\tEnter number of elements: ";
                std::cin >> num;
                double* arr = new double[num];

                for (int i = 0; i < num; i++) {
                    std::cout << "\t\tEnter [" << i << "] element: ";
                    std::cin >> arr[i];
                }
                Heap<double>* tmp = new Heap(arr, num);
                doubleHeap.emplace_back(tmp);
                std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                delete[] arr;
                break;
            }
            case (2): {
                if (!doubleHeap.size()) {
                    std::cout << "\t\t\x1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << doubleHeap.size()
                          << " heaps. Choose the index of heap to print"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, doubleHeap.size() - 1);

                heapDoubleOperations(doubleHeap.at(index), doubleHeap); // here
                break;
            }
            case (3): {
                if (!doubleHeap.size()) {
                    std::cout << "\t\t\x1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << doubleHeap.size()
                          << " heaps. Choose the index of heap to print"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, doubleHeap.size() - 1);

                std::cout << *(doubleHeap[index]) << std::endl;

                break;
            }
            case (4): {
                // ... Tests
                break;
            }
            case (5): {
                if (!doubleHeap.size()) {
                    std::cout << "\tx1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << doubleHeap.size()
                          << " heaps. Choose the index of heap to delete"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, doubleHeap.size() - 1);
                std::cout << "\t\x1B[91mDelete\033[0m " << index << " \x1B[91mheap?\033[0m" << std::endl;
                std::cout << "\t\t1| Yes\n"
                          << "\t\t0| No\n";
                std::cout << "\t\t: ";
                int lastChoice = getInt(0, 1);
                if (lastChoice) {
                    delete doubleHeap.at(index);
                    doubleHeap.erase(doubleHeap.begin() + index);
                    std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                }
                break;
            }
            default:
                return;
        }




        break;
    }
}

void heapMenuComplex(std::vector<Heap<Complex>*>& complexHeap) {
    while(true) {
        std::cout << "\tChoose option:\n"
                  << "\t\t1| Add heap\n"
                  << "\t\t2| Choose operation\n"
                  << "\t\t3| Print heaps\n"
                  << "\t\t4| Tests\n"
                  << "\t\t5| Delete\n"
                  << "\t\t0| exit\n"
                  << "\t\t: ";
        int choice = getInt(0, 5);
        switch (choice) {
            case (1): {
                int num;
                std::cout << "\t\tEnter number of elements: ";
                std::cin >> num;
                Complex* arr = new Complex[num];

                for (int i = 0; i < num; i++) {
                    std::cout << "\t\tEnter [" << i << "] element: ";
                    arr[i] = getComplex();
                }
                Heap<Complex>* tmp = new Heap(arr, num);
                complexHeap.emplace_back(tmp);
                std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                delete[] arr;
                break;
            }
            case (2): {
                if (!complexHeap.size()) {
                    std::cout << "\t\t\x1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << complexHeap.size()
                          << " heaps. Choose the index of heap to print"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, complexHeap.size() - 1);

                heapComplexOperations(complexHeap.at(index), complexHeap);

                break;
            }
            case (3): {
                if (!complexHeap.size()) {
                    std::cout << "\t\t\x1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << complexHeap.size()
                          << " heaps. Choose the index of heap to print"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, complexHeap.size() - 1);


                (complexHeap[index])->print();
//                printComplex(complexHeap[index]);

                break;
            }
            case (4): {
                // ... Tests
                break;
            }
            case (5): {
                if (!complexHeap.size()) {
                    std::cout << "\tx1B[91mYou haven't have any heaps yet.\033[0m" << std::endl;
                    break;
                }
                std::cout << "\tYou have " << complexHeap.size()
                          << " heaps. Choose the index of heap to delete"
                          << std::endl;
                std::cout << "\t\t: ";
                int index = getInt(0, complexHeap.size() - 1);
                std::cout << "\t\x1B[91mDelete\033[0m " << index << " \x1B[91mheap?\033[0m" << std::endl;
                std::cout << "\t\t1| Yes\n"
                          << "\t\t0| No\n";
                std::cout << "\t\t: ";
                int lastChoice = getInt(0, 1);
                if (lastChoice) {
                    delete complexHeap.at(index);
                    complexHeap.erase(complexHeap.begin() + index);
                    std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                }
                break;
            }
            default:
                return;
        }




        break;
    }
}



void heapIntOperations(Heap<int>* heap, std::vector<Heap<int>*>& intHeap) {
    std::cout << "\tChoose option:\n"
              << "\t\t1| Insert item\n"
              << "\t\t2| Remove item\n"
              << "\t\t3| Search item\n"
              << "\t\t4| Search sub heap\n"
              << "\t\t5| Cut heap\n"
              << "\t\t6| Write to file\n"
              << "\t\t7| Insert from file\n"
              << "\t\t0| exit\n"
              << "\t\t: ";
    int choice = getInt(0, 7);
    switch (choice) {
        case(1) : {
            std::cout << "\t\tEnter value: ";
            int value;
            std::cin >> value;
            heap->insert(value);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(2) : {
            std::cout << "\t\tEnter value: ";
            int value;
            std::cin >> value;
            heap->remove(value);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(3) : {
            std::cout << "\t\tEnter value: ";
            int value;
            std::cin >> value;
            bool result = heap->searchItem(value);
            if (result)
                std::cout << "\t\t\x1B[92mItem exists\033[0m" << std::endl;
            else
                std::cout << "\t\t\x1B[91mItem doesn't exist\033[0m" << std::endl;
            break;
        }
        case(4) : {
            std::cout << "\tYou have " << intHeap.size()
                      << " heaps.\n\tChoose the index of heap for searching it in this heap."
                      << std::endl;
            std::cout << "\t\t: ";
            int index = getInt(0, intHeap.size() - 1);
            bool result = heap->searchSubHeap(*(intHeap.at(index)));
            if (result)
                std::cout << "\t\t\x1B[92mThis heap exists\033[0m" << std::endl;
            else
                std::cout << "\t\t\x1B[91mThis heap doesn't exist\033[0m" << std::endl;
            break;
        }
        case(5) : {
            std::cout << "\t\tEnter value: ";
            int value;
            std::cin >> value;
            Heap<int>* result = heap->cut(value);
            if (!result)
                std::cout << "\t\t\x1B[91mItem with this value doesn't exist\033[0m" << std::endl;
            else {
                std::cout << "\tResult: " << std::endl;
                std::cout << *result << std::endl;
                std::cout << "Save this heap?" << std::endl;
                std::cout << "\t\t1| Yes\n"
                          << "\t\t0| No\n";
                std::cout << "\t\t: ";
                int choice = getInt(0, 1);
                if (choice) {
                    intHeap.emplace_back(result);
                    std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                }
            }
            break;
        }
        case(6) : {
            std::cout << "\t\tEnter file path: ";
            std::string path;
            std::cin >> path;
            heap->writeToFile(path);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(7) : {
            std::cout << "\t\tEnter file path: ";
            std::string path;
            std::cin >> path;
            heap->insertFromFile(path);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        default : {
            return;
            break;
        }
    }
}

void heapDoubleOperations(Heap<double>* heap, std::vector<Heap<double>*>& doubleHeap) {
    std::cout << "\tChoose option:\n"
              << "\t\t1| Insert item\n"
              << "\t\t2| Remove item\n"
              << "\t\t3| Search item\n"
              << "\t\t4| Search sub heap\n"
              << "\t\t5| Cut heap\n"
              << "\t\t6| Write to file\n"
              << "\t\t7| Insert from file\n"
              << "\t\t0| exit\n"
              << "\t\t: ";
    int choice = getInt(0, 7);
    switch (choice) {
        case(1) : {
            std::cout << "\t\tEnter value: ";
            double value;
            std::cin >> value;
            heap->insert(value);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(2) : {
            std::cout << "\t\tEnter value: ";
            double value;
            std::cin >> value;
            heap->remove(value);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(3) : {
            std::cout << "\t\tEnter value: ";
            double value;
            std::cin >> value;
            bool result = heap->searchItem(value);
            if (result)
                std::cout << "\t\t\x1B[92mItem exists\033[0m" << std::endl;
            else
                std::cout << "\t\t\x1B[91mItem doesn't exist\033[0m" << std::endl;
            break;
        }
        case(4) : {
            std::cout << "\tYou have " << doubleHeap.size()
                      << " heaps.\n\tChoose the index of heap for searching it in this heap."
                      << std::endl;
            std::cout << "\t\t: ";
            int index = getInt(0, doubleHeap.size() - 1);
            bool result = heap->searchSubHeap(*(doubleHeap.at(index)));
            if (result)
                std::cout << "\t\t\x1B[92mThis heap exists\033[0m" << std::endl;
            else
                std::cout << "\t\t\x1B[91mThis heap doesn't exist\033[0m" << std::endl;
            break;
        }
        case(5) : {
            std::cout << "\t\tEnter value: ";
            double value;
            std::cin >> value;
            Heap<double>* result = heap->cut(value);
            if (!result)
                std::cout << "\t\t\x1B[91mItem with this value doesn't exist\033[0m" << std::endl;
            else {
                std::cout << "\tResult: " << std::endl;
                std::cout << *result << std::endl;
                std::cout << "Save this heap?" << std::endl;
                std::cout << "\t\t1| Yes\n"
                          << "\t\t0| No\n";
                std::cout << "\t\t: ";
                int choice = getInt(0, 1);
                if (choice) {
                    doubleHeap.emplace_back(result);
                    std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                }
            }
            break;
        }
        case(6) : {
            std::cout << "\t\tEnter file path: ";
            std::string path;
            std::cin >> path;
            heap->writeToFile(path);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(7) : {
            std::cout << "\t\tEnter file path: ";
            std::string path;
            std::cin >> path;
            heap->insertFromFile(path);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        default : {
            return;
            break;
        }
    }
}

void heapComplexOperations(Heap<Complex>* heap, std::vector<Heap<Complex>*>& complexHeap) {
    std::cout << "\tChoose option:\n"
              << "\t\t1| Insert item\n"
              << "\t\t2| Remove item\n"
              << "\t\t3| Search item\n"
              << "\t\t4| Search sub heap\n"
              << "\t\t5| Cut heap\n"
              << "\t\t6| Write to file\n"
              << "\t\t7| Insert from file\n"
              << "\t\t0| exit\n"
              << "\t\t: ";
    int choice = getInt(0, 7);
    switch (choice) {
        case(1) : {
            std::cout << "\t\tEnter value: ";
            Complex value;
            value = getComplex();
            heap->insert(value);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(2) : {
            std::cout << "\t\tEnter value: ";
            Complex value;
            value = getComplex();
            heap->remove(value);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(3) : {
            std::cout << "\t\tEnter value: ";
            Complex value;
            value = getComplex();
            bool result = heap->searchItem(value);
            if (result)
                std::cout << "\t\t\x1B[92mItem exists\033[0m" << std::endl;
            else
                std::cout << "\t\t\x1B[91mItem doesn't exist\033[0m" << std::endl;
            break;
        }
        case(4) : {
            std::cout << "\tYou have " << complexHeap.size()
                      << " heaps.\n\tChoose the index of heap for searching it in this heap."
                      << std::endl;
            std::cout << "\t\t: ";
            int index = getInt(0, complexHeap.size() - 1);
            bool result = heap->searchSubHeap(*(complexHeap.at(index)));
            if (result)
                std::cout << "\t\t\x1B[92mThis heap exists\033[0m" << std::endl;
            else
                std::cout << "\t\t\x1B[91mThis heap doesn't exist\033[0m" << std::endl;
            break;
        }
        case(5) : {
            std::cout << "\t\tEnter value: ";
            Complex value;
            value = getComplex();
            Heap<Complex>* result = heap->cut(value);
            if (!result)
                std::cout << "\t\t\x1B[91mItem with this value doesn't exist\033[0m" << std::endl;
            else {
                std::cout << "\tResult: " << std::endl;
                result->print();
                std::cout << "Save this heap?" << std::endl;
                std::cout << "\t\t1| Yes\n"
                          << "\t\t0| No\n";
                std::cout << "\t\t: ";
                int choice = getInt(0, 1);
                if (choice) {
                    complexHeap.emplace_back(result);
                    std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
                }
            }
            break;
        }
        case(6) : {
            std::cout << "\t\tEnter file path: ";
            std::string path;
            std::cin >> path;
            heap->writeToFile(path);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        case(7) : {
            std::cout << "\t\tEnter file path: ";
            std::string path;
            std::cin >> path;
            heap->insertFromFile(path);
            std::cout << "\t\t\x1B[92mSuccess\033[0m" << std::endl;
            break;
        }
        default : {
            return;
            break;
        }
    }
}