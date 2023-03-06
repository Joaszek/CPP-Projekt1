//
// Created by Joachim on 04.03.2023.
//

#ifndef CPP_PROJEKT1_TAB_H
#define CPP_PROJEKT1_TAB_H
#include <stdlib.h>

using namespace std;

class Tablica{
public:

    int  *tab;
	int size=0; //at given moment
	int number=-1;
    int index=-1;
    int length; //final length

    void add_element_at_the_beginning(int liczba);
    void add_element_at_the_end(int liczba);
    void add_element_at_given_position(int liczba, int indeks);

    void delete_element(int indeks);

    void find_element(int liczba);

    void wyswietl_tablice();
    void menu_tablicy();
    void pomiar_czasu(int rozmiar);
};
#endif //CPP_PROJEKT1_TAB_H
