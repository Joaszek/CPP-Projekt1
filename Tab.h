//
// Created by Joachim on 04.03.2023.
//

#ifndef CPP_PROJEKT1_TAB_H
#define CPP_PROJEKT1_TAB_H
#include <stdlib.h>

using namespace std;

class Tab{
public:

    Tab();
    ~Tab();
    int  *tab;
	int size=0; //at given moment
	int number=-1;
    int index=-1;
    int length; //final length

    void add_element_at_the_beginning(int number);
    void add_element_at_the_end(int number);
    void add_element_at_given_position(int number, int index);

    void delete_element(int index);
    void create_array_from_file();
    void find_element(int number);
    void generate_array(int length);
    void print_array();
    void array_menu();
    void measure_time();
};
#endif //CPP_PROJEKT1_TAB_H
