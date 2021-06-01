#include "Menu.h"

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
                // ...
                break;
            }
            case (3): {
                // ...
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
            // ...
            break;
        }
        case(5) : {
            // ...
            break;
        }
        case(6) : {
            // ...
            break;
        }
        case(7) : {
            // ...
            break;
        }
        default : {
            // ...
            break;
        }
    }
}