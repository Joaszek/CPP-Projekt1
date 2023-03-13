#include <iostream>
#include "Kopiec.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <cmath>
using namespace std;

Kopiec::Kopiec()
{
}

void Kopiec::heapify(int array_in[], int array_size, int subtree_root_index){

	//array_in - tablica wejściowa
	//array_size - rozmiar tablicy
	//subtree_root_index - index największego elementu
    int largest_value = subtree_root_index;
    int left = 2 * subtree_root_index + 1;
    int right = 2 * subtree_root_index + 2;

	//sprawdzenie czy dzieci są większe od rodzica
    if (left < array_size && array_in[left] > array_in[largest_value]){
        largest_value = left;
    }

    if (right < array_size && array_in[right] > array_in[largest_value]){
        largest_value = right;
    }
	//sprawdzenie czy największa wartość jest węzłem
    if (largest_value != subtree_root_index){
        swap(array_in[subtree_root_index], array_in[largest_value]);
        heapify(array_in, array_size, largest_value);
    }
}

void Kopiec::construct_heap(int array_in[], int array_size)
{
	//index ostatniego węzła 
    int last_non_leaf_node = (array_size / 2) - 1;

	//każdy węzeł od końca
    for(int subtree_root_index = last_non_leaf_node; subtree_root_index >= 0; subtree_root_index -= 1){
        heapify(array_in, array_size, subtree_root_index);
    }
}

void Kopiec::wyswietl_kopiec(int array_in[], int array_size){
		
		int el_na_p, p, il_p, il_spacji, il_el_na_p;
		int j;
		for(j = 0; pow(2, j) <= array_size; j++){

        }
	  	il_p = j;	  	  
		p = 0; 	  
		int k = 0;
		 	  
		while(p < il_p)
		{
			il_spacji = pow(2, il_p - p+1) - 1;
			el_na_p = pow(2, p);
			il_el_na_p = 0;
			
			for(int i = 0; i < il_spacji/2; i++){
					cout << " ";
			}
			while(il_el_na_p < el_na_p && k < array_size){
				cout << array_in[k];
				k++;
				il_el_na_p++;				
				for(int i = 0; i < il_spacji; i++){
					cout << " ";
				}
			}
			p++;
			cout << "\n";	
		}	
		cout << "\nKopiec w postaci tablicy:\n";
		for(int i = 0; i < array_size; i++){
			cout << array_in[i] << " ";
		} 
	}