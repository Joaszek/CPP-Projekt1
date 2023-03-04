#include <conio.h>
#include <string>
#include <windows.h>
#include "List.h"

using namespace std;


List::List() {
    List::front = nullptr;
    List::tail = nullptr;
    *List::size = 0;
}

List::~List() {

}

void List::add_element_at_the_beginning(int number) {
    if(List::front == nullptr){
        List::front = new ListElement;
        List::front->previous=nullptr;
        List::front ->number = number;
        List::front ->next = List::tail;


        List::tail = new ListElement;
        List::tail -> previous = List::front;
        List::tail ->number = NULL;
        List::tail ->next = nullptr;
        *List::size++;
        cout << List::size<<endl;
    }else{
        ListElement *p = new ListElement;
        p->number = number;
        p->previous = nullptr;
        p->next = List::front;
        List::front=p;
        *List::size++;
        cout << List::size<<endl;

    }
}

void List::add_element_at_the_end(int number) {
    if(List::size==0){
        add_element_at_the_beginning(number);
    }else{
        ListElement *p = new ListElement;

        p->number = number;
        p->next = List::tail;
        p->previous = List::tail->previous;
        List::tail->previous->next = p;
        List::tail->previous = p;

        *List::size++;
    }
}

void List::add_element(int number) {
    cout << "Size: "<<*List::size<<endl;
    if(List::size!=0){
        int index = std::rand() % *List::size;
        ListElement *p = new ListElement;
        ListElement *temp = List::front;

        int i =0;
        cout <<"index: "<<index<<endl;
        while(temp->next){
            if(i==index)break;
            temp=temp->next;
            i++;
        }
        p->number = number;
        p->next = temp->next;
        p->previous = temp;

        temp->next->previous = p;
        temp->next = p;
    }else{
        add_element_at_the_beginning(number);
    }
}

void List::delete_element_at_the_beginning(ListElement **head) {
    cout << "Delete element at the beginning"<<endl;
}

void List::delete_element_at_the_end(ListElement **head) {
    cout << "Delete element at the end"<<endl;
}

void List::delete_element(ListElement **head, int number) {
    cout << "Delete element"<<endl;
}

void List::print_list() {
    ListElement *p = List::front;
    while( p )
    {
        cout << p->number <<endl;
        p = p->next;
    }
}


int List::get_list_size(ListElement **head) {
    cout << "List size"<<endl;
    return 1;
}

void List::time_difference( ListElement **head, int time) {

}

void List::menu_list() {
    ListElement *head;
    List *list = new List();
    head = NULL;

    int option = -1;
    int size = 0;
    string file_name;
    int length;

    while (option != 7) {

        printf("\nChoose option\n");
        printf("0. Add element at the beginning\n");
        printf("1. Add element at the end\n");
        printf("2. Add element at random position\n");

        printf("3. Delete first element\n");
        printf("4. Delete last element\n");
        printf("5. Delete element at given position\n");

        printf("6. Show list\n");
        printf("7. Go back to main menu\n");

        scanf("%i", &option);

        switch (option) {
            case 0:{
                //add element at the beginning
                int number_to_add;
                printf("Enter value to add at the beginning: ");
                scanf("%i", &number_to_add);

                list->add_element_at_the_beginning(number_to_add);
            }
                break;
            case 1: {
                //add element at the end
                int number_to_add;
                printf("Enter value to add at the end: ");
                scanf("%i", &number_to_add);

                list->add_element_at_the_end(number_to_add);
            }
                break;
            case 2: {
                //add element at random position
                int temp;
                printf("Enter value to add: ");
                scanf("%i", &temp);
                add_element(temp);
                list ->print_list();
            }
                break;
            case 3: {
                //delete first item
                delete_element_at_the_beginning(&head);
            }
                break;
            case 4: {
                //delete last element
                delete_element_at_the_end(&head);
            }
                break;
            case 5: {
                //delete chosen element
                int number =0;
                delete_element(&head,number);
            }
                break;
            case 6:
                list->print_list();
                break;
            case 7:
                head = NULL;
                break;

            default:
                printf("Enter correct option");
                Sleep(2000);
                break;
        }
    }
}
