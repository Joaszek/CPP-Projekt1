#include "Tree.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <chrono>

using namespace std;

void Tree::tree_menu()
{

    head = NULL;
    int option = -1;
    size = 0;
    string file_name;
    int length;
    while (option != 0)
    {

        cout << "\nChoose option" << endl;
        cout << "1.Build tree from file" << endl;
        cout << "2.Delete node with given value" << endl;
        cout << "3.Add node" << endl;
        cout << "4.Check if tree contains node" << endl;
        cout << "5.Generate tree with given value" << endl;
        cout << "6.Measure time" << endl;
        cout << "7.Go back to main menu" << endl;

        scanf("%i", &option);

        switch (option)
        {
        case 0:
            head = NULL;
            break;

        case 1:
        {
            cout << "Enter file name: " << endl;
            cin >> file_name;
            size = 0;
            ifstream file(file_name.c_str()); // osobna funkcja
            string size_of_tree;
            getline(file, size_of_tree);
            length = atoi(size_of_tree.c_str());
            head = NULL;
            while (size < length)
            {
                string number_to_add_to_tree;
                getline(file, number_to_add_to_tree);
                number = atoi(number_to_add_to_tree.c_str());
                add_element(number);
            }
            file.close();
        }
        break;
        case 2:
            cout << "Enter node you want to delete " << endl;
            scanf("%i", &number);
            if (size == 1)
            {
                head = NULL;
                size = 0;
            }
            else
                delete_root();
            break;
        case 3:
            cout << "Enter node value you want to add: " << endl;
            scanf("%i", &number);
            add_element(number);
            break;
        case 4:
            cout << "Enter node value to check: " << endl;
            scanf("%i", &number);
            find_element(number);
            break;
        case 5:
            srand(time(NULL));
            cout << "Enter tree size: " << endl;
            scanf("%i", &length);
            size = 0;
            head = NULL;
            while (size < length)
            {
                number = std::rand();
                add_element(number);
            }
            break;
        case 6:
            measure_time();    
            break;
        case 8:
            return;
        default:
            cout << "Enter correct option: ";
            Sleep(2000);
            break;
        }
    }
}
void Tree::print_tree(string sp, string sn, RBTNode *p)
{

    if (size == 0)
        cout << ("Tree is empty");
    else
    {
        string cr, cl, cp;
        cr = cl = cp = "  ";
        cr[0] = 218;
        cr[1] = 196;
        cl[0] = 192;
        cl[1] = 196;
        cp[0] = 179;
        string t;

        if (p != &S)
        {
            t = sp;
            if (sn == cr)
                t[t.length() - 2] = ' ';
            print_tree(t + cp, cr, p->right_son);
            t = t.substr(0, sp.length() - 2);
            cout << t << sn << p->color << ":" << p->number << endl;

            t = sp;
            if (sn == cl)
                t[t.length() - 2] = ' ';
            print_tree(t + cp, cl, p->left_son);
        }
    }
}
void Tree::add_element(int number)
{
    if (size == 0)
    {
        S.color = 'B'; // Inicjujemy stra�nika
        S.father = &S;
        S.left_son = &S;
        S.right_son = &S;
        head = &S;
    }
    RBTNode *X, *Y;

    X = new RBTNode;  // Tworzymy nowy w�ze�
    X->left_son = &S; // Inicjujemy pola
    X->right_son = &S;
    X->father = head;
    X->number = number;
    if (X->father == &S)
    {
        head = X; // X staje si� korzeniem
    }
    else
    {
        while (true) // Szukamy li�cia do zast�pienia przez X
        {
            if (number < X->father->number)
            {
                if (X->father->left_son == &S)
                {
                    X->father->left_son = X; // X zast�puje lewy li��
                    break;
                }
                X->father = X->father->left_son;
            }
            else
            {
                if (X->father->right_son == &S)
                {
                    X->father->right_son = X; // X zast�puje prawy li��
                    break;
                }
                X->father = X->father->right_son;
            }
        }
        X->color = 'R'; // W�ze� kolorujemy na czerwono
        while ((X != head) && (X->father->color == 'R'))
        {
            if (X->father == X->father->father->left_son)
            {
                Y = X->father->father->right_son; // Y -> wujek X
                if (Y->color == 'R')              // Przypadek 1
                {
                    X->father->color = 'B';
                    Y->color = 'B';
                    X->father->father->color = 'R';
                    X = X->father->father;
                    continue;
                }

                if (X == X->father->right_son) // Przypadek 2
                {
                    X = X->father;
                    rotation_to_the_left(X);
                }

                X->father->color = 'B'; // Przypadek 3
                X->father->father->color = 'R';
                rotation_to_the_right(X->father->father);
                break;
            }
            else
            { // Przypadki lustrzane
                Y = X->father->father->left_son;
                if (Y->color == 'R') // Przypadek 1
                {
                    X->father->color = 'B';
                    Y->color = 'B';
                    X->father->father->color = 'R';
                    X = X->father->father;
                    continue;
                }

                if (X == X->father->left_son) // Przypadek 2
                {
                    X = X->father;
                    rotation_to_the_right(X);
                }

                X->father->color = 'B'; // Przypadek 3
                X->father->father->color = 'R';
                rotation_to_the_left(X->father->father);
                break;
            }
        }
    }
    head->color = 'B';
    size++;
}
void Tree::rotation_to_the_left(RBTNode *A)
{
    RBTNode *B, *p;
    B = A->right_son;
    if (B != &S)
    {
        p = A->father;
        A->right_son = B->left_son;
        if (A->right_son != &S)
            A->right_son->father = A;

        B->left_son = A;
        B->father = p;
        A->father = B;

        if (p != &S)
        {
            if (p->left_son == A)
                p->left_son = B;
            else
                p->right_son = B;
        }
        else
            head = B;
    }
}
void Tree::rotation_to_the_right(RBTNode *A)
{
    RBTNode *B, *p;
    B = A->left_son;
    if (B != &S)
    {
        p = A->father;
        A->left_son = B->right_son;
        if (A->left_son != &S)
            A->left_son->father = A;

        B->right_son = A;
        B->father = p;
        A->father = B;

        if (p != &S)
        {
            if (p->left_son == A)
                p->left_son = B;
            else
                p->right_son = B;
        }
        else
            head = B;
    }
}
void Tree::delete_element(int number)
{
    RBTNode *Y, *X;

    X = head;
    while ((X != &S) && (X->number != number))
        if (number < X->number)
            X = X->left_son;
        else
            X = X->right_son;
    if (X == head)
    {
        if (X->right_son == &S)
        {
            head = X->left_son;
            X->left_son->father = &S;

            delete X;
        }
        else
        {
            Y = next(X);

            if (Y->right_son == &S)
            {
                if (Y->father->left_son == Y)
                    Y->father->left_son = &S;
                else
                    Y->father->right_son = &S;
            }
            else
            {
                Y->right_son->father = Y->father;
                if (Y->father->left_son == Y)
                {
                    Y->father->left_son = Y->right_son;
                }
                else
                {
                    Y->father->right_son = Y->right_son;
                }
            }

            head->number = Y->number;
            delete Y;
        }
    }
    else
    {
        if ((X->left_son == &S) && (X->right_son == &S))
        {
            if (X->father->left_son == X)
                X->father->left_son = &S;
            else
                X->father->right_son = &S;
            if (X->color == 'B')
                rebuilt_structure(X->father);
            delete X;
        }
        else if (X->right_son == &S)
        {
            if (X->father->left_son == X)
                X->father->left_son = X->left_son;
            else
                X->father->right_son = X->left_son;
            if (X->color == 'B')
                rebuilt_structure(X->left_son);

            delete X;
        }
        else
        {
            Y = next(X);

            if (Y->right_son == &S)
            {
                if (Y->father->left_son == Y)
                    Y->father->left_son = &S;
                else
                    Y->father->right_son = &S;
            }
            else
            {
                Y->right_son->father = Y->father;
                if (Y->father->left_son == Y)
                {
                    Y->father->left_son = Y->right_son;
                }
                else
                {
                    Y->father->right_son = Y->right_son;
                }
            }

            X->number = Y->number;
            if (X->color == 'B')
                rebuilt_structure(X);
            delete Y;
        }
    }
    head->color = 'B';
    size--;
}
void Tree::delete_root()
{
    RBTNode *Y, *X;

    X = head;
    if ((X->left_son == &S) && (X->right_son == &S))
    {
        head = NULL;
    }
    else if (X->right_son == &S)
    {
        if (X->father->left_son == X)
            X->father->left_son = X->left_son;
        else
            X->father->right_son = X->left_son;
        if (X->color == 'B')
            rebuilt_structure(X->left_son);

        delete X;
    }
    else if (X->left_son == &S)
    {
        if (X->father->right_son == X)
            X->father->right_son = X->right_son;
        else
            X->father->right_son = X->right_son;

        rebuilt_structure(X->right_son);
        delete X;
    }
    else
    {
        Y = next(X);
        if (Y->right_son == &S)
        {
            if (Y->father->left_son == Y)
            {
                Y->father->left_son = &S;
            }
            else
            {
                Y->father->right_son = &S;
            }
        }
        else
        {
            Y->right_son->father = Y->father;
            if (Y->father->left_son == Y)
            {
                Y->father->left_son = Y->right_son;
            }
            else
            {
                Y->father->right_son = Y->right_son;
            }
        }

        X->number = Y->number;
        rebuilt_structure(X);
        delete Y;
    }
    head->color = 'B';
    size--;
}
void Tree::rebuilt_structure(RBTNode *X)
{
    RBTNode *W;

    while ((X != head) && (X->color == 'B'))
    {

        if (X == X->father->left_son)
        {
            W = X->father->right_son;

            if (W->color == 'R')
            { // Przypadek 1
                W->color = 'B';
                X->father->color = 'R';
                rotation_to_the_left(X->father);
                W = X->father->right_son;
            }

            if ((W->left_son->color == 'B') && (W->right_son->color == 'B'))
            { // Przypadek 2
                W->color = 'R';
                X = X->father;
                continue;
            }

            if (W->right_son->color == 'B')
            { // Przypadek 3
                W->left_son->color = 'B';
                W->color = 'R';
                rotation_to_the_right(W);
                W = X->father->right_son;
            }

            W->color = X->father->color; // Przypadek 4
            X->father->color = 'B';
            W->right_son->color = 'B';
            rotation_to_the_left(X->father);
            X = head; // To spowoduje zako�czenie p�tli
        }
        else
        { // Przypadki lustrzane
            W = X->father->left_son;

            if (W->color == 'R')
            { // Przypadek 1
                W->color = 'B';
                X->father->color = 'R';
                rotation_to_the_right(X->father);
                W = X->father->left_son;
            }

            if ((W->left_son->color == 'B') && (W->right_son->color == 'B'))
            { // Przypadek 2
                W->color = 'R';
                X = X->father;
                continue;
            }

            if (W->left_son->color == 'B')
            { // Przypadek 3
                W->right_son->color = 'B';
                W->color = 'R';
                rotation_to_the_left(W);
                W = X->father->left_son;
            }

            W->color = X->father->color; // Przypadek 4
            X->father->color = 'B';
            W->left_son->color = 'B';
            rotation_to_the_right(X->father);
            X = head; // To spowoduje zako�czenie p�tli
        }
    }
}
RBTNode *Tree::minimum(RBTNode *p)
{
    if (p != &S)
        while (p->left_son != &S)
            p = p->left_son;
    return p;
}

RBTNode *Tree::next(RBTNode *p)
{

    RBTNode *r;

    if (p != &S)
    {
        if (p->right_son != &S)
            return minimum(p->right_son);
        else
        {
            r = p->father;
            while ((r != &S) && (p == r->right_son))
            {
                p = r;
                r = r->father;
            }
            return r;
        }
    }
    return &S;
}
void Tree::find_element(int number)
{
    RBTNode *p;

    p = head;
    while ((p != &S) && (p->number != number))
        if (number < p->number)
            p = p->left_son;
        else
            p = p->right_son;
    if (p == &S)
        cout <<"Element nie znajduje sie w drzewie");
    else
        cout <<"Element znajduje sie w drzewie");
}

void Tree::measure_time()
{
    const int NUMBER_OF_ITERATIONS = 20;
    string file_name;
    ofstream file;

    file.open(file_name);
    srand(time(NULL));

    int tab_test[NUMBER_OF_ITERATIONS];

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
    {
        tab_test[NUMBER_OF_ITERATIONS] = rand() % 16;
    }

    head = NULL;
    size = 0;
    for (int i = 0; i < 100; i++)
    {
        auto begin = chrono::steady_clock::now();

        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            add_element(number);
        }

        auto end = chrono::steady_clock::now();

        file << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";

        begin = chrono::steady_clock::now();

        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            delete_root();
        }

        end = chrono::steady_clock::now();

        file << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";
    }
}
