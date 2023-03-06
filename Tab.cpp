//
// Created by Joachim on 04.03.2023.
//
#ifndef tab_cpp
#define tab_cpp


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <chrono>
#include "Tab.h"

using namespace std;


	void Tablica::menu_tablicy(){
        int option=-1;
        string filename;

        while(option!=0)
        {

            printf("\nChoose option?\n");
            printf("1. Build array from file\n");
            printf("2. Delete element at given position\n");
            printf("3. Add element at given position\n");
            printf("4. Check if array contains number\n");
            printf("5. Generate array with chosen length\n");
            printf("6. Print array\n");
            printf("7. Measure time\n");
            printf("8. Go back to main menu\n");

            scanf("%i", &option);

            switch (option)
            {
            case 1:
            	{
            	int  *tab;
            	size = 0;
                tab = new int[rozmiar];
                printf("Podaj nazwe pliku, z którego chcesz wczytac tablice: ");
                cin >> nazwa_pliku;

                ifstream plik(nazwa_pliku.c_str());
                string rozmiar_1;
                getline(plik, rozmiar_1);
                dlugosc = atoi(rozmiar_1.c_str());


                while(rozmiar < dlugosc)
                {
                    string liczba_1;
                    getline(plik, liczba_1);
                    liczba = atoi(liczba_1.c_str());
                    dodaj_element(liczba, rozmiar);
                }
                wyswietl_tablice();
                plik.close();
                }break;
            case 2:
                printf("Wpisz indeks elementu, ktory chcesz usunac: ");
                scanf("%i", &indeks);
                usun_element(indeks);
                wyswietl_tablice();
                break;
            case 3:
                printf("Wpisz liczbe jaka chcesz dodac: ");
                scanf("%i", &liczba);
                printf("Wpisz indeks: ");
                scanf("%i", &indeks);
                dodaj_element(liczba, indeks);
	            wyswietl_tablice();
				break;
            case 4:
                printf("Wpisz element, ktory chcesz sprawdzic, czy znajduje sie w tablicy: ");
                scanf("%i", &liczba);
                znajdz_element(liczba);
                break;
            case 5:
            	rozmiar = 0;
            	tablica = new int[rozmiar];
                srand(time(NULL));
                printf("Podaj dlugosc tablicy, która chcesz wygenerowac: ");
                scanf("%i", &dlugosc);

                while(rozmiar < dlugosc)
                {
                    liczba = std::rand();
                    dodaj_element_na_ostatnim_miejscu(liczba);
                }
                wyswietl_tablice();
                break;
            case 6:
                wyswietl_tablice();
                break;
            case 7:
            	pomiar_czasu(1000);
            	pomiar_czasu(2500);
            	pomiar_czasu(5000);
            	pomiar_czasu(7500);
            	pomiar_czasu(10000);
            	pomiar_czasu(15000);
            	pomiar_czasu(25000);
            	pomiar_czasu(50000);
            	pomiar_czasu(75000);
            	pomiar_czasu(100000);

            	break;
            case 8:
                rozmiar = 0;
                break;
            default:
                printf("Podaj wlasciwa opcje.");
                Sleep(2000);
                break;

            }
        }
    }
	void Tablica::dodaj_element_na_ostatnim_miejscu(int liczba){
		int *kopia = new int[rozmiar];
		for(int i = 0; i < rozmiar - 1; i++){
			kopia[i] = tablica[i];
		}
		rozmiar++;

		tablica = new int[rozmiar];
		for(int i = 0; i < rozmiar - 1; i++){
			tablica[i] = kopia[i];
		}
		tablica[rozmiar-1] = liczba;
		delete [] kopia;
	}
	void Tablica::dodaj_element_na_pierwszym_miejscu(int liczba){
		int *kopia = tablica;
		rozmiar++;

		tablica = new int[rozmiar];
		tablica[0] = liczba;
		for(int i = 0; i < rozmiar - 1; i++){
			tablica[i+1] = kopia[i];
		}
		delete [] kopia;
	}
    void Tablica::dodaj_element(int liczba, int indeks){
		int *kopia = tablica;
		rozmiar++;
		tablica = new int[rozmiar];
		for(int i = 0; i < rozmiar - 1; i++){
				if(i >= indeks)
					tablica[i+1] = kopia[i];
				else
					tablica[i] = kopia[i];
			}
        if(indeks >= rozmiar)
            tablica[rozmiar-1] = liczba;
        else
            tablica[indeks] = liczba;
		delete [] kopia;
	}
	void Tablica::usun_element(int indeks){
		int *kopia = tablica;
		rozmiar--;

		tablica = new int[rozmiar];
		for(int i = 0; i < rozmiar; i++){
			if( i >= indeks)
				tablica[i] = kopia[i+1];
			else
			   	tablica[i] = kopia[i];
		}
		delete [] kopia;
	}
	void Tablica::znajdz_element(int liczba){
		int i = 0;
		while(i < rozmiar && liczba != tablica[i]){
			i++;
		}
		if(i < rozmiar)
			std::cout << "Liczba znajduje sie w tablicy.";
		else
		{
			std::cout << "Liczba nie znajduje sie w tablicy.";
		}

	}
	void Tablica::wyswietl_tablice(){
        for(int i = 0; i < rozmiar; i++)
			cout << tablica[i] << " ";
	}
    void Tablica::pomiar_czasu(int wielkosc){
        string nazwa;
        string txt = ".txt";
        string rozmiar1;
        rozmiar1 = to_string(wielkosc);
        nazwa = "Tablica_DodawanieNaPierwszymMiejscu_";
        nazwa = nazwa + rozmiar1+txt;

        ofstream fout;
        fout.open(nazwa);
        srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int  *tablica;
            rozmiar = 0;
            tablica = new int[rozmiar];
            for(int i = 0; i < wielkosc; i++)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(liczba);
            }
            for(int i = 0; i < 150; i++)
            {
                liczba = std::rand();
                auto begin = std::chrono::steady_clock::now();
                dodaj_element_na_pierwszym_miejscu(liczba);
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ";
            }
            fout << "\n";
        }
        fout.close();

        nazwa = "Tablica_DodawanieNaOstatnimMiejscu_";
        nazwa = nazwa + rozmiar1+txt;
                fout.open(nazwa);
        srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int  *tablica;
            rozmiar = 0;
            tablica = new int[rozmiar];
            for(int i = 0; i < wielkosc; i++)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(liczba);
            }
            for(int i = 0; i < 150; i++)
            {
                liczba = std::rand();
                auto begin = std::chrono::steady_clock::now();
                dodaj_element_na_ostatnim_miejscu(liczba);
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ";
            }
            fout << "\n";
        }
        fout.close();
                nazwa = "Tablica_DodawanieNaLosowymMiejscu_";
        nazwa = nazwa + rozmiar1+txt;
                fout.open(nazwa);
        srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int  *tablica;
            rozmiar = 0;
            tablica = new int[rozmiar];
            for(int i = 0; i < wielkosc; i++)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(liczba);
            }
            for(int i = 0; i < 150; i++)
            {
                liczba = std::rand();
                indeks = std::rand();
                auto begin = std::chrono::steady_clock::now();
                dodaj_element(liczba, indeks);
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ";
            }
            fout << "\n";
        }
        fout.close();
        nazwa = "Tablica_UsuwanieNaPierwszymMiejscu_";
        nazwa = nazwa + rozmiar1+txt;
        fout.open(nazwa);
        srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int  *tablica;
            rozmiar = 0;
            tablica = new int[rozmiar];
            for(int i = 0; i < wielkosc; i++)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(liczba);
            }
            for(int i = 0; i < 150; i++)
            {
                auto begin = std::chrono::steady_clock::now();
                usun_element(0);
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ";
            }
            fout << "\n";
        }
        fout.close();
        nazwa = "Tablica_UsuwanieNaOstatnimMiejscu_";
        nazwa = nazwa + rozmiar1+txt;
        fout.open(nazwa);
        srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int  *tablica;
            rozmiar = 0;
            tablica = new int[rozmiar];
            for(int i = 0; i < wielkosc; i++)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(liczba);
            }
            for(int i = 0; i < 150; i++)
            {
                auto begin = std::chrono::steady_clock::now();
                usun_element(rozmiar);
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ";
            }
            fout << "\n";
        }
        fout.close();
        nazwa = "Tablica_UsuwanieNaLosowymMiejscu_";
        nazwa = nazwa + rozmiar1+txt;
        fout.open(nazwa);
        srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int  *tablica;
            rozmiar = 0;
            tablica = new int[rozmiar];
            for(int i = 0; i < wielkosc; i++)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(liczba);
            }
            for(int i = 0; i < 150; i++)
            {
                indeks = std::rand();
                auto begin = std::chrono::steady_clock::now();
                usun_element(indeks);
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ";
            }
            fout << "\n";
        }
        fout.close();
        nazwa = "Tablica_SzukanieElementu_";
        nazwa = nazwa + rozmiar1+txt;
        fout.open(nazwa);
        srand(time(NULL));
        for(int i = 0; i < 100; i++)
        {
            int  *tablica;
            rozmiar = 0;
            tablica = new int[rozmiar];
            for(int i = 0; i < wielkosc; i++)
            {
                liczba = std::rand();
                dodaj_element_na_ostatnim_miejscu(liczba);
            }
            for(int i = 0; i < 150; i++)
            {
                liczba = std::rand();
                auto begin = std::chrono::steady_clock::now();
                znajdz_element(liczba);
                auto end = std::chrono::steady_clock::now();
                fout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ";
            }
            fout << "\n";
        }
        fout.close();
    }
#endif
