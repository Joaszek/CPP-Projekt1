#include <conio.h>
#include <string>
#include <windows.h>
#include "List.h"

using namespace std;


List::List() {
    this->front = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

List::~List() {

}

void List::add_element_at_the_beginning(int number) {
    if (front == nullptr) {
        front = new ListElement;
        front->previous = nullptr;
        front->number = number;
        front->next = tail;


        tail = new ListElement;
        tail->previous = front;
        tail->number = NULL;
        tail->next = nullptr;
        size++;
        cout << List::size << endl;
    } else {
        ListElement *p = new ListElement;
        p->number = number;
        p->previous = nullptr;
        p->next = front;
        front = p;
        size++;
        cout << size << endl;

    }
}

void List::add_element_at_the_end(int number) {
    if (size == 0) {
        add_element_at_the_beginning(number);
    } else {
        ListElement *p = new ListElement;

        p->number = number;
        p->next = tail;
        p->previous = tail->previous;
        tail->previous->next = p;
        tail->previous = p;

        size++;
    }
}

void List::add_element(int number) {
//nie dziala
    if (size != 0) {
        int index = (std::rand() % size);

        ListElement *p = new ListElement;

        ListElement *temp = front;

        int i = 0;

        while (temp&&i<index) {
            temp = temp->next;
            i++;
        }

        auto *s = temp->previous;

        p->number = number;

        p->next = temp;

        p->previous = temp->previous;

        s->next = p;

        temp->previous = p;

    } else {
        add_element_at_the_beginning(number);
    }
}

void List::delete_element_at_the_beginning() {
//    size--;
//    auto *p = front->next;
//    delete front;
//    front = p;
    remove_element(front);
}
void List::remove_element(ListElement *element)
{
    size--;
    if(element->previous ){
        element->previous->next = element->next;
    }
    else{
        front = element->next;
    }
    if( element->next ){
        element->next->previous = element->previous;
    }
    else{
        tail = element->previous;
    }
    delete element;
}
void List::delete_element_at_the_end() {
    //nie dziala
//    size--;
//    auto *p = tail->previous;
//    p->next= nullptr;
//    delete tail;
//    tail=p;
    remove_element(tail);
}

void List::delete_element(int number) {
    ListElement *p = front;
    ListElement *temp;
    while(p->next){
        if(p->number==number){
            temp=p->previous;
            p->previous->next=p->next;
            p->next->previous = temp;
            delete p;
            break;
        }
        p=p->next;
    }

}

void List::print_list() {
    ListElement *p = this->front;
    while (p) {
        cout << p->number << endl;
        p = p->next;
    }
}


void List::menu_list() {
    List list;

    int option = -1;
    string file_name;
    add_element_at_the_beginning(0);
    add_element_at_the_beginning(1);
    add_element_at_the_beginning(2);
    add_element_at_the_beginning(3);
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
            case 0: {
                //add element at the beginning
                int number_to_add;
                printf("Enter value to add at the beginning: ");
                scanf("%i", &number_to_add);

                add_element_at_the_beginning(number_to_add);
            }
                break;
            case 1: {
                //add element at the end
                int number_to_add;
                printf("Enter value to add at the end: ");
                scanf("%i", &number_to_add);

                add_element_at_the_end(number_to_add);
            }
                break;
            case 2: {
                //add element at random position
                int temp;
                printf("Enter value to add: ");
                scanf("%i", &temp);
                add_element(temp);
                print_list();
            }
                break;
            case 3: {
                //delete first item
                delete_element_at_the_beginning();
            }
                break;
            case 4: {
                //delete last element
                delete_element_at_the_end();
            }
                break;
            case 5: {
                //delete chosen element
                int number = 0;
                delete_element(number);
            }
                break;
            case 6:
                print_list();
                break;
            case 7:
                break;

            default:
                printf("Enter correct option");
                Sleep(2000);
                break;
        }
    }
}
