//#include "Menu.h"
//
//
//void PrintMenu()
//{
//    std::cout << "----Menu----" << std::endl;
//    std::cout << "1. Добавить элемент в дерево." << std::endl;
//    std::cout << "2. Вывод элементов дерева." << std::endl;
//    std::cout << "3. Функция Map. (+1)" << std::endl;
//    std::cout << "4. Функция Where. (>0)" << std::endl;
//    std::cout << "5. Функция извлечения поддерева." << std::endl;
//    std::cout << "6. Поиск элемента на вхождения в дерево." << std::endl;
//    std::cout << "7. Поиск поддерева на вхождения в дерево." << std::endl;
//    std::cout << "8. Тесты." << std::endl;
//    std::cout << "9. Выход." << std::endl;
//}
//
//void menuFloat()
//{
//    int choice = 0;
//    BinaryTree<float>* tree = new BinaryTree<float>();
//    BinaryTree<float>* tree2 = new BinaryTree<float>();
//    BinaryTree<float>* tree3 = new BinaryTree<float>();
//    BinaryTree<float>* tree4 = new BinaryTree<float>();
//    BinaryTree<float>* tree5 = new BinaryTree<float>();
//    float *f = new float;
//    float* f1 = new float;
//    float * f2 = new float;
//    float *f3 = new float;
//
//    while (choice != 9) {
//
//        PrintMenu();
//        std::cin >> choice;
//        int i = 1;
//        int j = 1;
//
//        switch (choice)
//        {
//            case 1:
//                while (i == 1)
//                {
//                    f = new float;
//                    std::cout << "Введите элемент: \n(Если он первый , то он будет корнем вашего дерева.)" << std::endl;
//                    std::cin >> *f;
//                    tree->insert(*f);
//                    std::cout << "Продолжит ввод? \n1. Да.\n!=1. Нет." << std::endl;
//                    std::cin >> i;
//                }
//                break;
//            case 2:
//                std::cout << *tree << std::endl;
//                break;
//            case 3:
////                tree2 = tree->Map(plusOne);
////                std::cout << *tree2 << std::endl;
//                break;
//            case 4:
////                tree3 = tree->filter(BigZero);
////                std::cout << *tree3 << std::endl;
//                break;
//            case 5:
//                std::cout << "Введите корень поддерева:" << std::endl;
//                std::cin >> *f1;
//                tree4 = tree->cut(*f1);
//                std::cout << *tree4 << std::endl;
//                break;
//            case 6:
//                std::cout << "Введите элемент для поиска на вхождение:" << std::endl;
//                std::cin >> *f2;
//                if (tree->searchItem(*f2))
//                    std::cout << "Ваш элемент входит в дерево." << std::endl;
//                else
//                    std::cout << "Ваш элемент не входит в дерево." << std::endl;
//                break;
//            case 7:
//                while (j == 1) {
//                    f3 = new float;
//                    std::cout << "Введите элементы поддерева для поиска: \n(Если он первый , то он будет корнем вашего дерева.)" << std::endl;
//                    std::cin >> *f3;
//                    tree5->insert(*f3);
//                    std::cout << "Продолжит ввод? \n1. Да.\n!=1. Нет." << std::endl;
//                    std::cin >> j;
//                }
//                std::cout << *tree5 << std::endl;
//                if (tree->searchTree(*tree5))
//                    std::cout << "Ваше поддерево входит в дерево." << std::endl;
//                else
//                    std::cout << "Ваше поддерево не входит в дерево." << std::endl;
//                break;
//            case 8:
////                Test(1);
//                break;
//            case 9:
//                break;
//            default:
//                std::cout << "Такой команды нет!" << std::endl;
//                break;
//        }
//    }
//}
//
//void menuComplex()
//{
//    int choice = 0;
//    BinaryTree<Complex>* tree = new BinaryTree<Complex>();
//    BinaryTree<Complex>* tree2 = new BinaryTree<Complex>();
//    BinaryTree<Complex>* tree3 = new BinaryTree<Complex>();
//    BinaryTree<Complex>* tree4 = new BinaryTree<Complex>();
//    BinaryTree<Complex>* tree5 = new BinaryTree<Complex>();
//    Complex *f1 = new Complex(0, 0);
//    Complex *f2 = new Complex(0, 0);
//    Complex *f3 = new Complex(0, 0);
//    Complex *f = new Complex(0, 0);
//
//    while (choice != 9) {
//
//        PrintMenu();
//        std::cin >> choice;
//        int k = 1;
//        int j = 1;
//
//        double r = 0, i = 0;
//        double r1 = 0, i1 = 0;
//        double r2 = 0, i2 = 0;
//        double r3 = 0, i3 = 0;
//
//
//        switch (choice)
//        {
//            case 1:
//                while (k == 1) {
//                    f = new Complex(0, 0);
//                    std::cout << "Введите элемент: \n(Если он первый , то он будет корнем вашего дерева.)" << std::endl;
//                    std::cout << "Введите действительную часть: ";
//                    std::cin >> r;
//                    std::cout << "Введите мнимую часть: ";
//                    std::cin >> i;
//                    f->cin(r, i);
//                    tree->insert(*f);
//                    std::cout << "Продолжит ввод? \n1. Да.\n!=1. Нет." << std::endl;
//                    std::cin >> k;
//                }
//                break;
//            case 2:
//                std::cout << *tree << std::endl;
//                break;
//            case 3:
//
////                tree2 = tree->Map(plusOne);
//                break;
//            case 4:
//
////                tree3 = tree->Where(BigZero);
//                break;
//            case 5:
//
//                std::cout << "Введите корень поддерева:" << std::endl;
//                std::cout << "Введите действительную часть: ";
//                std::cin >> r1;
//                std::cout << "Введите мнимую часть: ";
//                std::cin >> i1;
//                f1->cin(r1, i1);
//                tree4 = tree->cut(*f1);
//                std::cout << *tree4 << std::endl;
//                break;
//            case 6:
//                std::cout << "Введите элемент для поиска на вхождение:" << std::endl;
//                std::cout << "Введите действительную часть: ";
//                std::cin >> r2;
//                std::cout << "Введите мнимую часть: ";
//                std::cin >> i2;
//                f2->cin(r2, i2);
//                if (!(tree->searchItem(*f2)))
//                    std::cout << "Ваш элемент не входит в дерево." << std::endl;
//                else
//                    std::cout << "Ваш элемент входит в дерево." << std::endl;
//                break;
//            case 7:
//
//                while (j == 1) {
//                    std::cout << "Введите элементы поддерева для поиска: \n(Если он первый , то он будет корнем вашего дерева.)" << std::endl;
//                    std::cout << "Введите действительную часть: ";
//                    std::cin >> r3;
//                    std::cout << "Введите мнимую часть: ";
//                    std::cin >> i3;
//                    f3->cin(r3, i3);
//                    tree->insert(*f3);
//                    std::cout << "Продолжит ввод? \n1. Да.\n!=1. Нет." << std::endl;
//                    std::cin >> i;
//                }
//                if (!(tree->searchTree(*tree5)))
//                    std::cout << "Ваше поддерево не входит в дерево." << std::endl;
//                else
//                    std::cout << "Ваше поддерево входит в дерево." << std::endl;
//                break;
//            case 8:
////                Test(2);
//                break;
//            case 9:
//                break;
//            default:
//                std::cout << "Такой команды нет!" << std::endl;
//                break;
//        }
//    }
//}
//
//void menu()
//{
//    int choice = 0 ;
//    std::cout << "-Menu-" << std::endl;
//    std::cout << "Тип дерево:" << std::endl;
//    std::cout << "1. Float\n2. Complex" << std::endl;
//    std::cin >> choice;
//    switch (choice)
//    {
//        case 1:
//            menuFloat();
//            break;
//        case 2:
//            menuComplex();
//            break;
//        default:
//            std::cout << "Такого типа не сушествует!" << std::endl;
//            break;
//    }
//
//}