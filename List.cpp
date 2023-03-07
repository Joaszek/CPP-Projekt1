#include <conio.h>
#include <string>
#include <windows.h>
#include <chrono>
#include "List.h"
#include <fstream>
#include <iostream>

using namespace std;

List::List()
{
    this->front = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

List::~List()
{
}

void List::add_element_at_the_beginning(int number)
{
    //sprawdzamy czy glowa juz istnieje
    if (front == nullptr)
    {
        //tworzymy nowa glowe i ustawiamy jej poczatkowe wartosci
        front = new ListElement;
        front->previous = nullptr;
        front->number = number;
        front->next = tail;

        //tworzymy ogon i ustawiamy poczatkowe wartosci
        tail = new ListElement;
        tail->previous = front;
        tail->number = -1;
        tail->next = nullptr;
        size++;
        return;
    }
    //tworzymy nowa glowe i dodajemy ja na poczatek
    ListElement *p = new ListElement;
    front->previous = p;
    p->number = number;
    p->previous = nullptr;
    p->next = front;
    front = p;
    size++;
}

void List::add_element_at_the_end(int number)
{
    //sprawdzamy czy istnieje glowa, jezeli nie to wywolujemy funkcje poczatkowa
    if (size == 0)
    {
        add_element_at_the_beginning(number);
        return;
    }
    else
    {
        //tworzymy nowy element i dodajemy go na koniec
        ListElement *p = new ListElement;

        p->number = number;
        p->next = tail;
        p->previous = tail->previous;
        tail->previous->next = p;
        tail->previous = p;

        size++;
    }
}

void List::add_element(int number, int index)
{
    //sprawdzamy czy glowa istnieje, jezeli tak to tworzymy nowy element i losujemy mu pozycje
    if (size != 0)
    {
        if(index<0){
            cout << "Index out of bounds"<<endl;
        }
        else if (index == 0)
        {
            //jezeli index wynosi zero to tworzymy nowa glowe
            add_element_at_the_beginning(number);
            return;
        }
        else if (index == size - 1)
        {
            //jezeli index wynosi size-1 to tworzymy nowy ogon
            add_element_at_the_end(number);
            return;
        }
        else if(index>size+1){
            cout << "Index out of bounds"<<endl;
            return;
        }
        else
        {
            //tworzymy nowy element
            ListElement *p = new ListElement;

            ListElement *temp = front;

            //zmienna do tymczasowego indexu
            int i = 0;
            
            //idziemy w petli az dojdziemy na odpowiednie miejsce
            while (temp && i < index)
            {
                temp = temp->next;
                i++;
            }

            //pomocnicza zmienna do przechowania poprzedniej wartosci
            auto *s = temp->previous;

            //ustawiamy nowe dane
            p->number = number;

            p->next = temp;

            p->previous = temp->previous;

            s->next = p;

            temp->previous = p;
            return;
        }
    }
    else
    {
        //lista jest pusta wiec tworzymy nowa glowe
        add_element_at_the_beginning(number);
        return;
    }
}

void List::delete_element_at_the_beginning()
{
    //usuwamy element na poczatku
    remove_element(front);
    return;
}

void List::remove_element(ListElement *element)
{
    //zmniejszamy rozmiar listy
    size--;
    
    //jezeli element ma poprzednika to zmieniamy mu wartosc
    if (element->previous)
    {
        element->previous->next = element->next;
    }
    else
    {
        //ustawiamy nowa glowe
        front = element->next;
    }
    //jezeli element ma nastepnika to zmieniamy mu wartosc
    if (element->next)
    {
        element->next->previous = element->previous;
    }
    else
    {
        //zmieniamy wartosc dla ogona
        tail = element->previous;
    }
    delete element;
}

void List::delete_element_at_the_end()
{
    //zmniejszamy rozmiar
    size--;
    
    //przestawiamy wartosci
    auto *p = tail->previous;
    p->next = nullptr;
    //usuwamy ogon
    delete tail;

    //ustawiamy nowy ogon
    tail = p;
}

void List::delete_element(int number)
{
    //tworzymy pomocniczy element i iterujemy po nim az bedzie nullem
    ListElement *p = front;
    while (p)
    {
        //jezeli wartosc jest rowna szukanej to usuwamy element i zmieniamy wartosci poprzednika i nastepnika
        if (p->number == number)
        {
            if (p->previous == nullptr)
            {
                delete_element_at_the_beginning();
            }
            else if (p->next == nullptr)
            {
                delete_element_at_the_end();
            }
            else
            {
                p->previous->next = p->next;
                p->next->previous = p->previous;
            }
            delete p;
            return;
        }
        p = p->next;
    }
}

void List::print_list()
{
    //pokazujemy liste od przodu
    ListElement *p = this->front;
    while (p != tail && p != nullptr)
    {
        cout << p->number << " ";
        p = p->next;
    }
    cout << endl;

    //pokazujemy od konca
    p = this ->tail->previous;
    while (p != nullptr)
    {
        cout << p->number << " ";
        p = p->previous;
    }
}

void List::check_if_element_exists(int number)
{
    //tworzymy element pomocniczy którym będziemy iterowac
    //zaczynamy od poczatku

    ListElement *p = front;
    while (p)
    {
        //jezeli znalezlismy to pokazujemy
        if (p->number == number)
        {
            cout << "List contains that number" << endl;
            return;
        }
        p = p->next;
    }
    //nie udalo sie znalezc elementu
    cout << "List doesn't contains that number" << endl;
}

void List::measure_time()
{

    //otwieramy plik tekstowy
    ofstream file;
    file.open("scores_list.txt");

    //stala okreslajaca ilosc testow
    const int TEST_NUMBER = 800;
    int tab_test[TEST_NUMBER];

    //sprawdzamy czy udalo sie otworzyc plik
    if (!file.is_open())
    {
        cout << "Could not open file";
        return;
    }

    //zaczynamy testy
    for (int iteration = 0; iteration < 10; iteration++)
    {
        
        //tworzymy losowe zmienne
        for (int i = 0; i < TEST_NUMBER; i++)
        {
            tab_test[i] = std::rand() % (16);
        }
        //czyscimy liste jesli sa w niej elementy
        while (size > 0)
        {
            delete_element_at_the_end();
        }

        // dodajemy na poczatku i zaczynamy mierzyc czas
        auto begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++)
        {
            add_element_at_the_beginning(tab_test[i]);
        }
        auto end = chrono::steady_clock::now();

        //obliczamy roznice czasow
        auto duration_add_at_beginning = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        //cout << "adding at the beginning: " << duration_add_at_beginning << " microseconds" << endl;
        //wysylamy dane do pliku
        file << duration_add_at_beginning << ";";


        //analogicznie bedzie w nastepnych przypadkach

        // usuwamy na poczatku i zaczynamy mierzyc czas
        begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++)
        {
            delete_element_at_the_beginning();
        }
        end = chrono::steady_clock::now();

        auto duration_delete_element_at_the_beginning = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        //cout << "delete at the beginning: " << duration_delete_element_at_the_beginning << " microseconds" << endl;


        file << duration_delete_element_at_the_beginning << ";";

        // add at the end
        begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++)
        {
            add_element_at_the_end(tab_test[i]);
        }
        end = chrono::steady_clock::now();
        auto duration_add_element_at_the_end = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        
        //cout << "add at the end: " << duration_add_element_at_the_end << " microseconds" << endl;
        file << duration_add_element_at_the_end << ";";

        // delete element at the end
        begin = chrono::steady_clock::now();
        for (int i = 0; i < TEST_NUMBER; i++)
        {
            delete_element_at_the_end();
        }
        end = chrono::steady_clock::now();
        auto duration_delete_element_at_the_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                                                      end - begin)
                                                      .count();
        //cout << "delete at the end: " << duration_delete_element_at_the_end << " microseconds" << endl;
        file << duration_add_element_at_the_end << "\n";
    }
    file.close();
}

void List::load_from_file()
{

    //otwieramy plik
    string filename;
    fstream file;

    //pobieramy nazwe pliku
    cout << "Enter file name with txt extension:";
    cin >> filename;

    file.open(filename, ios::in);
    int size_to_enter;
    //jezeli udalo sie otworzyc plik to pobieramy dane z niego
    if (file.is_open())
    {
        string data;
        getline(file, data);
        size_to_enter = atoi(data.c_str());
        cout << "Size: " << size << endl;
        int value;
        while (getline(file, data))
        {
            value = atoi(data.c_str());
            add_element_at_the_end(value);
        }
    }
    file.close();
}

void List::menu_list()
{
    List list;

    int option = -1;
    string file_name;
    while (option != 6)
    {

        cout << "\nChoose option"<<endl;
        cout << "1.Load from file"<<endl;
        cout << "2.Add element at given position"<<endl;
        cout << "3.Delete element with given value"<<endl;
        cout << "4.Check if list contains number"<<endl;
        cout << "5.Measure time"<<endl;
        cout << "6.Go back to menu"<<endl;

        scanf("%i", &option);

        switch (option)
        {
        case 1:
        {
            // zaladuj z pliku
            load_from_file();
        }
        break;
        case 2:
        {
            // dodaj na wybranej pozycji
            int number_to_add;
            int index;
            cout << "Enter value to add: "<<endl;
            scanf("%i", &number_to_add);
            cout << "At which position you want to add: " << endl;
            cin >> index;
            add_element(number_to_add, index);
        }
        break;
        case 3:
        {
            // usun wybrany element
            int number = 0;
            cout << "Enter value to delete: "<<endl;
            scanf("%i", &number);
            delete_element(number);
        }
        break;
        case 4:
        {
            //sprawdzanie wartosci
            int number = 0;
            cout << "Enter value to check: "<<endl;
            scanf("%i", &number);
            check_if_element_exists(number);
        }
        break;
        case 5:
        {
            //testy
            measure_time();
        }
        break;
        case 6:
            return;
            
        default:
            cout << "Enter correct option"<<endl;
            Sleep(2000);
            break;
        }
        print_list();
    }
}
