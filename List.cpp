#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <conio.h>
#include "List.h"
#include <string>
#include <windows.h>

using namespace std;

void List::add_element_at_the_beginning(ListElement_typedef **head, int number) {
    cout << "Add element at the beginning"<<endl;
}

void List::add_element_at_the_end(ListElement_typedef **head, int number) {
    cout << "Add element at the end"<<endl;
}

void List::add_element(ListElement_typedef **head, int number, int position) {
    cout << "Add element"<<endl;
}

void List::delete_element_at_the_beginning(ListElement_typedef **head) {
    cout << "Delete element at the beginning"<<endl;
}

void List::delete_element_at_the_end(ListElement_typedef **head) {
    cout << "Delete element at the end"<<endl;
}

void List::delete_element(ListElement_typedef **head, int number) {
    cout << "Delete element"<<endl;
}

void List::print_list(ListElement_typedef **head) {
    cout << "Print list"<<endl;
}


int List::get_list_size(ListElement_typedef **head) {
    cout << "List size"<<endl;
    return 1;
}

void List::time_difference(int time, ListElement_typedef **head) {

}

void List::menu_list() {
    ListElement_typedef *head;
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

                add_element_at_the_beginning(&head,number_to_add);
            }
                break;
            case 1: {
                //add element at the end
                int number_to_add;
                printf("Enter value to add at the end: ");
                scanf("%i", &number_to_add);

                add_element_at_the_end(&head,number_to_add);
            }
                break;
            case 2: {
                //add element at random position
                int temp;
                int index;
                printf("Enter value to add: ");
                scanf("%i", &temp);
                index = std::rand() % get_list_size(&head);
                add_element(&head, temp, index);
                print_list(&head);
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
                print_list(&head);
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
