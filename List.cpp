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
    } else {
        ListElement *p = new ListElement;
        front->previous = p;
        p->number = number;
        p->previous = nullptr;
        p->next = front;
        front = p;
        size++;
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
    if (size != 0) {
        int index = (std::rand() % (size));
        if(index==0){
            add_element_at_the_beginning(number);

        }else if(index==size-1){
            add_element_at_the_end(number);
        }else{
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
        }



    } else {
        add_element_at_the_beginning(number);
    }
}

void List::delete_element_at_the_beginning() {

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
    size--;
    auto *p = tail->previous;
    p->next= nullptr;
    delete tail;
    tail=p;
}

void List::delete_element(int number) {
    ListElement *p = front;
    while(p){
        if(p->number==number){
            if(p->previous== nullptr){
                delete_element_at_the_beginning();
                return;
            }else if(p->next== nullptr){
                delete_element_at_the_end();
                return;
            }else{
                p->previous->next=p->next;
                p->next->previous = p->previous;
            }
            delete p;
            break;
        }
        p=p->next;
    }
}

void List::print_list() {
    ListElement *p = this->front;
    while (p!=tail&&p!= nullptr) {
        cout << p->number << endl;
        p = p->next;
    }
}


void List::menu_list() {
    List list;

    int option = -1;
    string file_name;
    add_element_at_the_beginning(10);
    add_element_at_the_beginning(12);
    add_element_at_the_beginning(23);
    add_element_at_the_beginning(30);
    while (option != 7) {

        printf("\nChoose option\n");
        printf("0. Add element at the beginning\n");
        printf("1. Add element at the end\n");
        printf("2. Add element at random position\n");

        printf("3. Delete first element\n");
        printf("4. Delete last element\n");
        printf("5. Delete element with given value\n");

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
                printf("Enter value to delete: ");
                scanf("%i", &number);
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
