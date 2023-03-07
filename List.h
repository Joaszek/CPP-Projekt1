#include <iostream>
#include <cstdlib>
using namespace std;

struct ListElement {
    int number;
    ListElement *previous, *next;
};

class List {

public:
    ListElement *front, *tail;
    int size =0;


    List();

    ~List();

    void add_element_at_the_beginning(int number);

    void add_element_at_the_end(int number);

    void add_element(int number, int index);

    void delete_element_at_the_beginning();

    void delete_element_at_the_end();

    void delete_element(int number);

    void print_list();

    void menu_list();
    void remove_element(ListElement *element);
    void check_if_element_exists(int number);
    void measure_time();
    void load_from_file();
};

