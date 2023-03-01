#include <iostream>
#include <stdlib.h>
using namespace std;

class List
{
    typedef struct ListElement
    {
        int number;
        struct ListElement *previous, *next;
    }ListElement_typedef;
    
    int size;
        
    List::List(/* args */)
    {
    }
    List::~List()
    {
    }
    void add_element_at_the_begginning(ListElement_typedef **head, int number);
    void add_element_at_the_end(ListElement_typedef **head, int number);
    void add_element(ListElement_typedef **head, int number, int position);

    void delete_element(ListElement_typedef **head, int number);

    void find_element(ListElement_typedef **head, int number);

    void print_list(ListElement_typedef **head, int direction);
    void menu_list();

    int get_list_size();

    void time_diffrence(int size, ListElement_typedef **head);
};

