#include <iostream>
using namespace std;


class Kopiec {

    public:
        Kopiec();
        void heapify(int array_in[], int array_size, int subtree_root_index);
        void construct_heap(int array_in[], int array_size);
        void print_heap(int array_in[], int array_size);
        void wyswietl_kopiec(int array_in[], int array_size);
};
