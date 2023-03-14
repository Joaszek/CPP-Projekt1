#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;


class Heap {

    public:
        int size = 0;
        int length=0;
        int number =-1;
        int heap[];

        void heapify(int array_in[], int array_size, int subtree_root_index);
        void construct_heap(int array_in[], int array_size);
        void print_heap(int array_in[], int array_size);
        void print_heap(int array_in[], int array_size);
        void add_element(int number);
        void delete_number(int number);
        void menu_heap();
        void find_element(int number);
        void generate_heap();
        void create_heap_from_file();
        void measure_time();
};
