//
// Created by Joachim on 04.03.2023.
//
#ifndef tab_cpp
#define tab_cpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <chrono>
#include "Tab.h"

using namespace std;

Tab::Tab()
{
}
Tab::~Tab()
{
}
void Tab::generate_array(int length)
{
    srand(time(NULL));
    tab = new int[length];
    for (int i = 0; i < length; i++)
    {
        number = rand() % 16;
        add_element_at_the_end(number);
    }
}
void Tab::create_array_from_file()
{
    string file_name;
    size =0;
    cout << "Enter file name: " << endl;
    cin >> file_name;

    fstream file;
    file.open(file_name);

    string size_of_array;
    getline(file, size_of_array);

    length = atoi(size_of_array.c_str());

    tab = new int[length];
    

    while (size < length)
    {
        string number_to_add;

        getline(file, number_to_add);

        number = atoi(number_to_add.c_str());

        tab[size] = number;
        cout << tab[size]<<endl;
        size++;
    }

    cout << "Size: "<<size<<endl;
    file.close();
}

void Tab::add_element_at_the_end(int number)
{
    cout << "1" << endl;
    // tworzymy nową tablice
    int *copy = new int[size];
    cout << "2" << endl;

    // przepisujemy wartosci do nowej tablicy
    for (int i = 0; i < size; i++)
    {
        copy[i] = tab[i];
    }
    cout << "3" << endl;

    size++; // zwiekszamy rozmiar o jeden dla nowego elementu
    cout << "4" << endl;

    // usuwamy starą tablice
    delete tab;
    cout << "5" << endl;

    // znajdujemy nowe miejsce dla tablicy
    tab = new int[size];
    cout << "6" << endl;

    // dodajemy wartości do nowej tablicy
    for (int i = 0; i < size - 1; i++)
    {
        tab[i] = copy[i];
    }
    cout << "7" << endl;

    // dodanie nowej wartosci
    tab[size - 1] = number;
    cout << "8" << endl;

    // usuwamy starą
    delete[] copy;
    cout << "9" << endl;
}
void Tab::add_element_at_the_beginning(int number)
{
    // tworzymy nową tablice
    int *copy = new int[size + 1];

    // przepisujemy wartosci do nowej tablicy
    for (int i = 0; i < size; i++)
    {
        copy[i + 1] = tab[i];
    }

    size++;
    // usuwamy starą tablice
    delete tab;

    // znajdujemy nowe miejsce dla tablicy
    tab = new int[size];

    // dodajemy nową wartosc do kopii
    copy[0] = number;

    // dodajemy wartości do nowej tablicy
    for (int i = 0; i < size; i++)
    {
        tab[i] = copy[i];
    }

    // usuwamy starą
    delete[] copy;
}
void Tab::add_element_at_given_position(int number, int index)
{
    // tworzymy wskaznik na tablice
    int *copy = tab;

    // zwiekszamy rozmiar o 1
    size++;

    // tworzymy nową tablice
    tab = new int[size];

    // dodajemy elementy do tablicy
    for (int i = 0; i < size - 1; i++)
    {
        // po nowym elemencie
        if (i >= index)
        {
            tab[i + 1] = copy[i];
        }
        // przed nowym elementem
        else
        {
            tab[i] = copy[i];
        }
    }
    // dodanie elementu na koniec tablicy jeśli indeks jest większy niż rozmiar
    if (index >= size)
    {
        tab[size - 1] = number;
    }
    // dodanie elementu do tablicy
    else
    {
        tab[index] = number;
    }

    // usuwanie tablicy
    delete[] copy;
}
void Tab::delete_element(int index)
{
    // tworzenie kopii
    int *copy = tab;

    // zmniejszanie rozmiaru
    size--;

    // tworzenie nowej tablicy
    tab = new int[size];

    // dodawanie elementów do tablicy
    for (int i = 0; i < size; i++)
    {
        // po starym elemencie
        if (i >= index)
        {
            tab[i] = copy[i + 1];
        }
        // przed starym elementem
        else
        {
            tab[i] = copy[i];
        }
    }
    // usuwanie kopii
    delete[] copy;
}
void Tab::find_element(int number)
{
    // sprawdzenie czy element znajduje sie w tablicy
    for (int i = 0; i < size; i++)
    {
        if (tab[i] == number)
        {
            cout << "Tab contains that number at index: " << i << endl;
            return;
        }
    }
    cout << "Tab doesn't contains that number" << endl;
}

void Tab::print_array()
{
    // wypisz liste
    for (int i = 0; i < size; i++){
        cout << tab[i] << " ";
    }
}
void Tab::measure_time()
{
    // ilosc iteracji
    const int NUMBER_OF_ITERATIONS = 4000;

    // tworzenie polaczenia z plikiem
    ofstream file;
    file.open("scores_tab.txt");
    srand(time(NULL));
    int tab_test[NUMBER_OF_ITERATIONS];
    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
    {
        tab_test[i] = std::rand() % 16;
    }

    

    int *tab;
    for (int i = 0; i < 100; i++)
    {
        // mierzenie czasu dla dodania na poczatku
        auto begin = std::chrono::steady_clock::now();
        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            add_element_at_the_beginning(number);
        }
        auto end = std::chrono::steady_clock::now();

        file << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";

        // mierzenie czasu dla usuwania na poczatku
        begin = std::chrono::steady_clock::now();
        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            delete_element(0);
        }
        end = std::chrono::steady_clock::now();
        file << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";

        // mierzenie czasu dla dodania na koncu
        begin = std::chrono::steady_clock::now();
        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            add_element_at_the_end(number);
        }
        end = std::chrono::steady_clock::now();

        file << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";

        // mierzenie czasu dla usuwania na koncu
        begin = std::chrono::steady_clock::now();
        for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
        {
            delete_element(size - 1);
        }
        end = std::chrono::steady_clock::now();
        file << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\n";
    }
    file.close();
}
void Tab::array_menu()
{
    int option = -1;
    string file_name;
    int *tab;
    while (option != 0)
    {

        printf("\nChoose option?\n");
        printf("1.Build array from file\n");
        printf("2.Add element at given position\n");
        printf("3.Delete element at given position\n");
        printf("4.Check if array contains number\n");
        printf("5.Generate array with chosen length\n");
        printf("6.Measure time\n");
        printf("7.Go back to main menu\n");

        scanf("%i", &option);

        switch (option)
        {
        case 1:
        {
            create_array_from_file();
        }
        break;
        case 2:
            printf("Add number you want to add: ");
            scanf("%i", &number);
            printf("Enter index: ");
            scanf("%i", &index);
            add_element_at_given_position(number, index);
            break;
        case 3:
            printf("Enter index of element you want to delete: ");
            scanf("%i", &index);
            delete_element(index);
            break;

        case 4:
            printf("Check element: ");
            scanf("%i", &number);
            find_element(number);
            break;
        case 5:
            delete tab;
            size = 0;
            printf("Enter array length: ");
            scanf("%i", &length);
            generate_array(length);
            break;
        case 6:
            measure_time();
            break;
        case 7:
            size = 0;
            return;
            break;
        default:
            printf("Podaj wlasciwa opcje.");
            Sleep(2000);
            break;
        }
        print_array();
    }
}
#endif
