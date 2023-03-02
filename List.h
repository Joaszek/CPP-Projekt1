#include <iostream>
#include <stdlib.h>
using namespace std;

class List {
public:
    typedef struct ListElement {
        int number;
        struct ListElement *previous, *next;
    } ListElement_typedef;

    int size;

    List() {

    }

    ~List() {

    }

    void add_element_at_the_beginning(ListElement_typedef **head, int number);

    void add_element_at_the_end(ListElement_typedef **head, int number);

    void add_element(ListElement_typedef **head, int number, int position);

    void delete_element_at_the_beginning(ListElement_typedef **head);

    void delete_element_at_the_end(ListElement_typedef **head);

    void delete_element(ListElement_typedef **head, int number);

    void print_list(ListElement_typedef **head);

    void menu_list();

    int get_list_size(ListElement_typedef **head);

    void time_difference(int time, ListElement_typedef **head);
};

