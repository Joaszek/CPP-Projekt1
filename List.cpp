#include <conio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include "List.h"
#include <fstream>

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
        tail->number = -1;
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
        return;
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
        if (index == 0) {
            add_element_at_the_beginning(number);
            return;
        } else if (index == size - 1) {
            add_element_at_the_end(number);
            return;
        } else {
            ListElement *p = new ListElement;

            ListElement *temp = front;

            int i = 0;

            while (temp && i < index) {
                temp = temp->next;
                i++;
            }

            auto *s = temp->previous;

            p->number = number;

            p->next = temp;

            p->previous = temp->previous;

            s->next = p;

            temp->previous = p;
            return;
        }
    } else {
        add_element_at_the_beginning(number);
        return;
    }
}

void List::delete_element_at_the_beginning() {

    remove_element(front);
    return;
}

void List::remove_element(ListElement *element) {
    size--;
    if (element->previous) {
        element->previous->next = element->next;

    } else {
        front = element->next;
    }
    if (element->next) {
        element->next->previous = element->previous;

    } else {
        tail = element->previous;
    }
    delete element;
}

void List::delete_element_at_the_end() {
    size--;
    auto *p = tail->previous;
    p->next = nullptr;
    delete tail;
    tail = p;
}

void List::delete_element(int number) {
    ListElement *p = front;
    while (p) {
        if (p->number == number) {
            if (p->previous == nullptr) {
                delete_element_at_the_beginning();
            } else if (p->next == nullptr) {
                delete_element_at_the_end();
            } else {
                p->previous->next = p->next;
                p->next->previous = p->previous;
            }
            delete p;
            return;
            //break;
        }
        p = p->next;
    }
}

void List::print_list() {
    ListElement *p = this->front;
    while (p != tail && p != nullptr) {
        cout << p->number << " ";
        p = p->next;
    }
}

void List::check_if_element_exists(int number) {
    ListElement *p = front;
    while (p) {
        if (p->number == number) {
            cout << "List contains that number" << endl;
            return;
        }
        p = p->next;
    }
    cout << "List doesn't contains that number" << endl;
}

void List::measure_time() {

    ofstream file;
    file.open("scores.txt");

    int TEST_NUMBER = 8000;
    int tab_test[TEST_NUMBER];

    if(file.is_open()){
        cout << "File open";
    }

    for(int iteration =0;iteration<1;iteration++){

        for (int i = 0; i < TEST_NUMBER; i++) {
            tab_test[i] = std::rand() % (16);
        }
        while (size > 0) {
            delete_element_at_the_end();
        }

        //adding at the beginning
        auto begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++) {
            add_element_at_the_beginning(tab_test[i]);
        }
        auto end = chrono::steady_clock::now();
        auto duration_add_at_beginning = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        cout << "adding at the beginning: " << duration_add_at_beginning << " microseconds" << endl;
        file << duration_add_at_beginning<<";";

        //delete at the beginning
        begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++) {
            delete_element_at_the_beginning();
        }
        end = chrono::steady_clock::now();
        auto duration_delete_element_at_the_beginning = std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - begin).count();
        cout << "delete at the beginning: " << duration_delete_element_at_the_beginning << " microseconds" << endl;
        file << duration_delete_element_at_the_beginning<<";";


        //add at the end
        begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++) {
            add_element_at_the_end(tab_test[i]);
        }
        end = chrono::steady_clock::now();
        auto duration_add_element_at_the_end = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        cout << "add at the end: " << duration_add_element_at_the_end << " microseconds" << endl;
        file << duration_add_element_at_the_end<<";";


        //delete element at the end
        begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++) {
            delete_element_at_the_end();
        }
        end = chrono::steady_clock::now();
        auto duration_delete_element_at_the_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - begin).count();
        cout << "delete at the end: " << duration_delete_element_at_the_end << " microseconds" << endl;
        file << duration_add_element_at_the_end<<"\n";
    }
    file.close();
}

void List::load_from_file() {

    string filename = "list";
    fstream file;

    cout << "Enter file name with txt extension: \n";
    cin >> filename;

    file.open(filename, ios::in);

    if(file.is_open()){
        string data;
        getline(file, data);
        size =  atoi(data.c_str());
        cout <<"Size: "<< size<<endl;
        int value;
        while(getline(file, data)){
            value = atoi(data.c_str());
            add_element_at_the_end(value);
        }
    }
    file.close();
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
        printf("8. Check if number exists\n");
        printf("9. Measure time\n");
        printf("10. Load from file");

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
            case 6: {
                print_list();

            }
                break;
            case 7:
                break;
            case 8: {
                int number = 0;
                printf("Enter value to check: ");
                scanf("%i", &number);
                check_if_element_exists(number);
            }
                break;
            case 9: {
                measure_time();
            }
                break;
            case 10: {
                load_from_file();
            }
                break;
            default:
                printf("Enter correct option");
                Sleep(2000);
                break;
        }
        print_list();
    }
}
