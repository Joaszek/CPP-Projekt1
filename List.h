#include <iostream>
#include <cstdlib>
using namespace std;

struct ListElement {
    int number;
    ListElement *previous, *next;
};

class List {
private:
    int number = 0;

public:
    ListElement *front, *tail;
    int *size = &number;


    List();

    ~List();

    void add_element_at_the_beginning(int number);

    void add_element_at_the_end(int number);

    void add_element(int number);

    void delete_element_at_the_beginning(ListElement **head);

    void delete_element_at_the_end(ListElement **head);

    void delete_element(ListElement **head, int number);

    void print_list();

    void menu_list();

    int get_list_size(ListElement **head);

    void time_difference(ListElement **head, int time);
};

