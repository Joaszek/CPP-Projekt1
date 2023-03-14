#include "Tree.h"
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

        cout << "Choose option" << endl;
        cout << "1.Build tree from file" << endl;
        cout << "2.Delete node with given value" << endl;
        cout << "3.Add node" << endl;
        cout << "4.Check if tree contains node" << endl;
        cout << "5.Generate tree with given value" << endl;
        cout << "6.Measure time" << endl;
        cout << "7.Go back to main menu" << endl;

        cin >> option;

        switch (option)
        {

        case 1:
        {
            size = 0;

            // wpisujemy nazwe pliku
            cout << "Enter file name: " << endl;
            cin >> file_name;
            // otwieramy plik
            fstream file;
            file.open(file_name, ios::in);

            if (file.is_open())
            {

                // zmienna do przechowania rozmiaru
                string size_of_tree;

                // pobieranie dlugosci z pliku
                getline(file, size_of_tree);
                length = atoi(size_of_tree.c_str());

                head = NULL;

                // dopoki aktualny rozmiar jest mniejszy od dlugosci podanej w pliku
                // wykonuj petle
                while (size < length)
                {
                    // pobieranie wartosci i dodawanie jej do drzewa
                    string number_to_add_to_tree;
                    getline(file, number_to_add_to_tree);
                    number = atoi(number_to_add_to_tree.c_str());
                    add_element(number);
                }
                file.close();
            }
            else
            {
                cout << "Could not open file" << endl;
            }
        }
        break;
        case 2:
            cout << "Enter node you want to delete " << endl;
            cin >> number;
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
            cin >> number;
            add_element(number);
            break;
        case 4:
            cout << "Enter node value to check: " << endl;
            cin >> number;
            find_element(number);
            break;
        case 5:
            srand(time(NULL));
            cout << "Enter tree size: " << endl;
            cin >> length;
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
        case 7:
            return;
        default:
            cout << "Enter correct option: ";
            Sleep(2000);
            break;
        }
        print_tree("", "", head);
    }
}
void Tree::print_tree(string sp, string sn, Red_Black_Node *p)
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

        if (p != &sentinel_node)
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
    // inicjujemy straznika
    if (size == 0)
    {
        sentinel_node.color = 'B';
        sentinel_node.father = &sentinel_node;
        sentinel_node.left_son = &sentinel_node;
        sentinel_node.right_son = &sentinel_node;
        head = &sentinel_node;
    }

    Red_Black_Node *node_to_add, *uncle;
    // Tworzymy nowy wezel
    node_to_add = new Red_Black_Node;

    // Inicjujemy pola
    node_to_add->left_son = &sentinel_node;
    node_to_add->right_son = &sentinel_node;
    node_to_add->father = head;
    node_to_add->number = number;

    // jezeli rodzic jest ustawiony na sentinel node wezel staje sie korzeniem
    if (node_to_add->father == &sentinel_node)
    {
        head = node_to_add;
    }
    else
    {
        while (true) // Szukamy liscia do zastspienia przez node_to_add
        {
            if (number < node_to_add->father->number)
            {
                // jezeli jest lisciem
                if (node_to_add->father->left_son == &sentinel_node)
                {
                    // node_to_add zastepuje lewy lisc
                    node_to_add->father->left_son = node_to_add;
                    break;
                }
                // lewy syn staje sie ojcem
                node_to_add->father = node_to_add->father->left_son;
            }
            else
            {
                // jezeli jest lisciem
                if (node_to_add->father->right_son == &sentinel_node)
                {
                    // node_to_add zastepuje prawy lisc
                    node_to_add->father->right_son = node_to_add;
                    break;
                }
                // prawy syn staje sie ojcem
                node_to_add->father = node_to_add->father->right_son;
            }
        }

        // ustawiamy kolor wezla na czerwony
        node_to_add->color = 'R';

        // ustawianie kolorow w drzewie
        while ((node_to_add != head) && (node_to_add->father->color == 'R'))
        {
            // sprawdzamy czy ojciec jest lewym synem
            if (node_to_add->father == node_to_add->father->father->left_son)
            {
                // uncle jest prawym bratem ojca node_to_add
                uncle = node_to_add->father->father->right_son;

                // przypadek 1
                if (uncle->color == 'R')
                {
                    node_to_add->father->color = 'B';
                    uncle->color = 'B';
                    node_to_add->father->father->color = 'R';
                    node_to_add = node_to_add->father->father;
                    continue;
                }

                // sprawdzamy czy node_to_add jest prawym synem
                // przypadek 2
                if (node_to_add == node_to_add->father->right_son)
                {
                    node_to_add = node_to_add->father;
                    rotation_to_the_left(node_to_add);
                }

                // przypadek 3
                node_to_add->father->color = 'B';
                node_to_add->father->father->color = 'R';
                rotation_to_the_right(node_to_add->father->father);
                break;
            }
            else
            {
                // przypadek analogiczny tylko z drugiej strony

                // uncle jest lewym bratem ojca
                uncle = node_to_add->father->father->left_son;

                // przypadek 1
                if (uncle->color == 'R')
                {
                    node_to_add->father->color = 'B';
                    uncle->color = 'B';
                    node_to_add->father->father->color = 'R';
                    node_to_add = node_to_add->father->father;
                    continue;
                }

                // przypadek 2
                if (node_to_add == node_to_add->father->left_son)
                {
                    node_to_add = node_to_add->father;
                    rotation_to_the_right(node_to_add);
                }

                // przypadek 3
                node_to_add->father->color = 'B';
                node_to_add->father->father->color = 'R';
                rotation_to_the_left(node_to_add->father->father);
                break;
            }
        }
    }
    head->color = 'B';
    size++;
}
void Tree::rotation_to_the_left(Red_Black_Node *A)
{
    // tworzymy pomocnicze wezly
    Red_Black_Node *B, *p;

    // ustawiamy wezel na prawego syna A
    B = A->right_son;
    if (B != &sentinel_node)
    {
        // p ustawiamy na ojca
        p = A->father;

        // ustawiamy wartosc prawego syna a
        A->right_son = B->left_son;

        // ustawiamy dziecki wskaznik na ojca
        if (A->right_son != &sentinel_node)
        {
            A->right_son->father = A;
        }

        // ustawiamy pozostale wartosci
        B->left_son = A;
        B->father = p;
        A->father = B;

        // jezeli p nie jest lisciem
        if (p != &sentinel_node)
        {
            // ustawiamy wartosci
            if (p->left_son == A)
            {
                p->left_son = B;
            }

            else
            {
                p->right_son = B;
            }
        }
        else
            head = B;
    }
}

// analogicznie do rotacji w lewo
void Tree::rotation_to_the_right(Red_Black_Node *A)
{
    Red_Black_Node *B, *p;
    B = A->left_son;
    if (B != &sentinel_node)
    {
        p = A->father;
        A->left_son = B->right_son;

        if (A->left_son != &sentinel_node)
        {
            A->left_son->father = A;
        }

        B->right_son = A;
        B->father = p;
        A->father = B;

        if (p != &sentinel_node)
        {
            if (p->left_son == A)
            {
                p->left_son = B;
            }

            else
            {
                p->right_son = B;
            }
        }
        else
            head = B;
    }
}
void Tree::delete_element(int number)
{

    Red_Black_Node *Y, *X;

    X = head;

    // znajdujemy odpowiedni wezel
    while ((X != &sentinel_node) && (X->number != number))
    {
        if (number < X->number)
        {
            X = X->left_son;
        }

        else
        {
            X = X->right_son;
        }
    }

    if (X == head)
    {
        // // usuwamy glowe gdy prawy syn jest lisciem
        // if (X->right_son == &sentinel_node)
        // {
        //     head = X->left_son;
        //     X->left_son->father = &sentinel_node;
        //     rebuilt_structure(head);
        //     delete X;
        // }
        // else
        // {
        //     // ustawiamy Y jako nastepnik
        //     Y = next_node(X);

        //     if (Y->right_son == &sentinel_node)
        //     {
        //         // jezeli Y jest lewym synem
        //         if (Y->father->left_son == Y)
        //         {
        //             Y->father->left_son = &sentinel_node;
        //         }
        //         else
        //         {
        //             Y->father->right_son = &sentinel_node;
        //         }
        //     }
        //     else
        //     {
        //         // Ustawiamy ojca prawego syna Y na ojca Y
        //         Y->right_son->father = Y->father;

        //         // jezeli Y jest lewym synem
        //         if (Y->father->left_son == Y)
        //         {
        //             Y->father->left_son = Y->right_son;
        //         }
        //         else
        //         {
        //             Y->father->right_son = Y->right_son;
        //         }
        //     }

        //     head->number = Y->number;
        //     delete Y;
        // }
        delete_root();
    }
    else
    {
        // jestesmy w lisciu i nie ma zadnego syna
        if ((X->left_son == &sentinel_node) && (X->right_son == &sentinel_node))
        {
            // sprawdzamy czy X jest po lewej stronie
            if (X->father->left_son == X)
            {
                X->father->left_son = &sentinel_node;
            }

            else
            {
                X->father->right_son = &sentinel_node;
            }

            // jezeli lisc jest czarny to robimy rebuilt poniewaz
            // na kazdej sciezce musi taka sama ilosc czarnych lisci
            if (X->color == 'B')
            {
                rebuilt_structure(X->father);
            }

            delete X;
        }
        // jezeli X nie ma prawego syna
        else if (X->right_son == &sentinel_node)
        {
            // sprawdzamy czy X jest lewym synem
            if (X->father->left_son == X)
            {
                // ustawiamy lewego syna ojca X na lewego syna X
                X->father->left_son = X->left_son;
            }

            else
            {
                // ustawiamy prawego syna ojca X na lewego syna X
                X->father->right_son = X->left_son;
            }

            // jezeli lisc jest czarny to robimy rebuilt poniewaz
            // na kazdej sciezce musi taka sama ilosc czarnych lisci
            if (X->color == 'B')
            {
                rebuilt_structure(X->left_son);
            }

            delete X;
        }
        // X nie ma lewego syna
        else
        {
            // szukamy nastepnika
            Y = next_node(X);

            // jezeli prawy syn nastepnika jest pusty
            if (Y->right_son == &sentinel_node)
            {
                // jezeli Y jest lewym synem
                if (Y->father->left_son == Y)
                {
                    Y->father->left_son = &sentinel_node;
                }

                else
                {
                    Y->father->right_son = &sentinel_node;
                }
            }
            // jezeli lewy syn nastepnika jest pusty
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
            {
                rebuilt_structure(X);
            }
            delete Y;
        }
    }

    head->color = 'B';
    size--;
}

void Tree::delete_root()
{
    Red_Black_Node *Y, *X;

    X = head;
    if ((X->left_son == &sentinel_node) && (X->right_son == &sentinel_node))
    {
        head = NULL;
    }
    // jezeli prawy syn jest pusty
    else if (X->right_son == &sentinel_node)
    {
        if (X->father->left_son == X)
        {
            X->father->left_son = X->left_son;
        }

        else
        {
            // ustawiamy lewego syna na nowego lewego syna
            X->father->right_son = X->left_son;
        }

        if (X->color == 'B')
            rebuilt_structure(X->left_son);

        delete X;
    }
    else if (X->left_son == &sentinel_node)
    {
        // przenosimy syna pozycje wyzej
        if (X->father->right_son == X)
        {
            X->father->right_son = X->right_son;
        }

        else
        {
            X->father->right_son = X->right_son;
        }

        rebuilt_structure(X->right_son);
        delete X;
    }
    else
    {
        Y = next_node(X);
        // sprawdzamy czy Y ma prawego syna
        if (Y->right_son == &sentinel_node)
        {

            if (Y->father->left_son == Y)
            {
                Y->father->left_son = &sentinel_node;
            }
            else
            {
                Y->father->right_son = &sentinel_node;
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
void Tree::rebuilt_structure(Red_Black_Node *X)
{
    Red_Black_Node *node;

    while ((X != head) && (X->color == 'B'))
    {

        if (X == X->father->left_son)
        {
            node = X->father->right_son;

            // przypadek 1
            if (node->color == 'R')
            {
                node->color = 'B';
                X->father->color = 'R';
                rotation_to_the_left(X->father);
                node = X->father->right_son;
            }

            // przypadek 2
            if ((node->left_son->color == 'B') && (node->right_son->color == 'B'))
            {
                node->color = 'R';
                X = X->father;
                continue;
            }

            // przypadek 3
            if (node->right_son->color == 'B')
            {
                node->left_son->color = 'B';
                node->color = 'R';
                rotation_to_the_right(node);
                node = X->father->right_son;
            }

            // przypadek 4
            node->color = X->father->color;
            X->father->color = 'B';
            node->right_son->color = 'B';
            rotation_to_the_left(X->father);
            // X = head;
        }
        else
        {
            node = X->father->left_son;

            // przypadek 1
            if (node->color == 'R')
            {
                node->color = 'B';
                X->father->color = 'R';
                rotation_to_the_right(X->father);
                node = X->father->left_son;
            }

            // przypadek 2
            if ((node->left_son->color == 'B') && (node->right_son->color == 'B'))
            {
                node->color = 'R';
                X = X->father;
                continue;
            }

            // przypadek 3
            if (node->left_son->color == 'B')
            {
                node->right_son->color = 'B';
                node->color = 'R';
                rotation_to_the_left(node);
                node = X->father->left_son;
            }

            // przypadek 4
            node->color = X->father->color;
            X->father->color = 'B';
            node->left_son->color = 'B';
            rotation_to_the_right(X->father);
            // X = head;
        }
        // warunek konczacy petle
        X = head;
    }
}
Red_Black_Node *Tree::minimum(Red_Black_Node *p)
{
    if (p != &sentinel_node)
        while (p->left_son != &sentinel_node)
            p = p->left_son;
    return p;
}

Red_Black_Node *Tree::next_node(Red_Black_Node *p)
{
    // tworzymy pomocniczą zmienną
    Red_Black_Node *r;

    // jezeli p nie jest straznikiem
    if (p != &sentinel_node)
    {
        // jezeli prawy syn p nie jest straznikiem
        if (p->right_son == &sentinel_node)
        {
            // r ustawiamy na ojca p
            r = p->father;

            // dopoki r jest rozne od straznika i p == prawemu synowi r
            // przypisujemy r do p
            // przypisujemy do r ojca r
            // jezeli p jest lewym synem to konczymy
            while ((r != &sentinel_node) && (p == r->right_son))
            {
                p = r;
                r = r->father;
            }
            return r;
        }
        // zwracamy minimum
        return minimum(p->right_son);
    }
    // zwracamy puste
    return &sentinel_node;
}
void Tree::find_element(int number)
{
    // tworzymy pomocniczy element
    Red_Black_Node *p;

    p = head;
    // iterujemy po kazdym elemencie
    // szukajac poprawnej wartosci
    while ((p != &sentinel_node) && (p->number != number))
        if (number < p->number)
        {
            p = p->left_son;
        }

        else
        {
            p = p->right_son;
        }

    if (p == &sentinel_node)
    {
        cout << "Element nie znajduje sie w drzewie" << endl;
    }

    else
    {
        cout << "Element znajduje sie w drzewie" << endl;
    }
}

void Tree::measure_time()
{
    const int NUMBER_OF_ITERATIONS = 20;
    string file_name = "scores_tree.txt";

    ofstream file(file_name, ios::out);
    cout << "1" << endl;

    srand(time(NULL));

    cout << "2" << endl;

    int tab_test[NUMBER_OF_ITERATIONS];

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
    {
        tab_test[i] = rand() % 16;
    }

    cout << "3" << endl;

    if (file.is_open())
    {
        cout << "open" << endl;
    }


    head = NULL;
    size = 0;
    for (int i = 0; i < 100; i++)
    {

        // dodawanie elementu
        auto begin = chrono::steady_clock::now();

        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            add_element(number);
        }
        cout << "4" << endl;

        auto end = chrono::steady_clock::now();
        cout << "5" << endl;
        auto duration = chrono::duration_cast<chrono::microseconds>(end - begin).count();

        cout << duration << "koniec\n";
        // dodanie wyniku do pliku scores_tree.txt
        file << duration << ";";

        // usuwanie korzenia
        begin = chrono::steady_clock::now();
        cout << "7" << endl;

        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            delete_root();
        }
        cout << "8" << endl;

        end = chrono::steady_clock::now();
        cout << "9" << endl;

        // dodanie wyniku do pliku scores_tree.txt
        file << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";
        cout << "10" << endl;
    }
    file.close();
}