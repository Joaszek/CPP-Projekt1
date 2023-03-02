#include <iostream>
#include <stdlib.h>
#include "Lista.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include "List.h"

using namespace std;

void List::add_element_at_the_begginning(ListElement_typedef **head, int number)
{
}
void List::add_element_at_the_end(ListElement_typedef **head, int number)
{
}
void List::add_element(ListElement_typedef **head, int number, int position)
{
}

void List::delete_element(ListElement_typedef **head, int number)
{
}

void List::find_element(ListElement_typedef **head, int number)
{
}

void List::print_list(ListElement_typedef **head, int direction)
{
}
void List::menu_list()
{
    ListElement_typedef *head;
    head = NULL;

    int option = -1;
    int size = 0;
    string file_name;
    int length;

    while (option != 0)
    {

        printf("\n\nChoose option\n");
        printf("1. Zbuduj liste z pliku.\n");
        printf("2. Usunac element o podanej wartosci.\n");
        printf("3. Dodaj elemnet na wybrana pozyjce.\n");
        printf("4. Sprawdz czy dana liczba znajduje sie na liscie.\n");
        printf("5. Wygeneruj liste o zadanej wielkosci.\n");
        printf("6. Wyswietl liste.\n");
        printf("7. Pomiar czasu metod.\n");
        printf("0. Wroc do glownego menu\n");

        scanf("%i", &option);

        switch (option)
        {
        case 0:
            head = NULL;
            break;

        case 1:
        {
            printf("Podaj nazwe pliku, z ktorego chcesz wczytac liste: ");
            cin >> file_name; //nazwa pliku
            size = 0; //
            ifstream file(file_name.c_str()); //zamiana stringa na tablice charow
            string first_row; // rozmiar listy
            getline(file, first_row); //pobranie rozmiaru listy
            length = atoi(row.c_str()); //zamiana stringa na inta
            head = NULL;
            while (size < length)
            {
                string number;
                getline(file, number);
                number_to_add = atoi(number.c_str());
                add_element_at_the_end(&head, number_to_add);
            }
            file.close();
            print_list(&head);
        }
        break;
        case 2:
            printf("Wpisz element, ktory chcesz usunac: ");
            scanf("%i", &liczba);
            if (rozmiar == 1)
            {
                head = NULL;
                rozmiar = 0;
            }
            else
                usun_element_po_indeksie(&head, liczba);
            wyswietl_liste(&head);
            break;
        case 3:
            printf("Wpisz liczbe jaka chcesz dodac: ");
            scanf("%i", &liczba);
            printf("Wpisz indeks: ");
            scanf("%i", &indeks);
            dodaj_element(&head, liczba, indeks);
            wyswietl_liste(&head);
            break;
        case 4:
            printf("Wpisz element, ktory chcesz sprawdzic, czy znajduje sie na liscie: ");
            scanf("%i", &liczba);
            znajdz_element(&head, liczba);
            break;
        case 5:
            srand(time(NULL));
            printf("Podaj dlugosc listy, kt�ra chcesz wygenerowac: ");
            scanf("%i", &dlugosc);
            rozmiar = 0;
            head = NULL;
            while (rozmiar < dlugosc)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(&head, liczba);
            }
            wyswietl_liste(&head);
            break;
        case 6:
            wyswietl_liste(&head);
            break;
        case 7:
            pomiar_czasu(1000, &head);
            pomiar_czasu(2500, &head);
            pomiar_czasu(5000, &head);
            pomiar_czasu(7500, &head);
            pomiar_czasu(10000, &head);
            pomiar_czasu(15000, &head);
            pomiar_czasu(25000, &head);
            pomiar_czasu(50000, &head);
            pomiar_czasu(75000, &head);
            pomiar_czasu(100000, &head);
            break;
        default:
            printf("Podaj wlasciwa opcje.");
            Sleep(2000);
            break;
        }
    }
}

int List::get_list_size()
{
}

void List::time_diffrence(int size, ListElement_typedef **head)
{
}