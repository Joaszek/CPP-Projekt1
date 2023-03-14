#include "Heap.h"
using namespace std;

void Heap::heapify(int array_in[], int array_size, int subtree_root_index)
{

	// array_in - tablica wejściowa
	// array_size - rozmiar tablicy
	// subtree_root_index - index największego elementu
	int largest_value = subtree_root_index;
	int left = 2 * subtree_root_index + 1;
	int right = 2 * subtree_root_index + 2;

	// sprawdzenie czy dzieci są większe od rodzica
	if (left < array_size && array_in[left] > array_in[largest_value])
	{
		largest_value = left;
	}

	if (right < array_size && array_in[right] > array_in[largest_value])
	{
		largest_value = right;
	}
	// sprawdzenie czy największa wartość jest węzłem
	if (largest_value != subtree_root_index)
	{
		swap(array_in[subtree_root_index], array_in[largest_value]);
		heapify(array_in, array_size, largest_value);
	}
}

void Heap::construct_heap(int array_in[], int array_size)
{
	// index ostatniego węzła
	int last_non_leaf_node = (array_size / 2) - 1;

	// każdy węzeł od końca
	for (int subtree_root_index = last_non_leaf_node; subtree_root_index >= 0; subtree_root_index -= 1)
	{
		heapify(array_in, array_size, subtree_root_index);
	}
}

void Heap::print_heap(int array_in[], int array_size)
{

	int el_na_p, p, il_p, il_spacji, il_el_na_p;
	int j;
	for (j = 0; pow(2, j) <= array_size; j++)
	{

	}
	il_p = j;
	p = 0;
	int k = 0;

	while (p < il_p)
	{
		il_spacji = pow(2, il_p - p + 1) - 1;
		el_na_p = pow(2, p);
		il_el_na_p = 0;

		for (int i = 0; i < il_spacji / 2; i++)
		{
			cout << " ";
		}
		while (il_el_na_p < el_na_p && k < array_size)
		{
			cout << array_in[k];
			k++;
			il_el_na_p++;
			for (int i = 0; i < il_spacji; i++)
			{
				cout << " ";
			}
		}
		p++;
		cout << "\n";
	}
	cout << "Heap as table:"<<endl;
	for (int i = 0; i < array_size; i++)
	{
		cout << array_in[i] << " ";
	}
}
void Heap::add_element(int number)
{
	int i, j;

	i = size;
	size++;
	j = (i - 1) / 2;

	while (i > 0 && heap[j] < number)
	{
		heap[i] = heap[j];
		i = j;
		j = (i - 1) / 2;
	}

	heap[i] = number;
}

void Heap::generate_heap()
{
	srand(time(NULL));
	size = 0;
	int dlugosc;
	cout << "Podaj size kopca, kt�ry chcesz wygenerowac: " << endl;
	scanf("%i", &dlugosc);
	while (size < dlugosc)
	{
		int number = std::rand();
		add_element(number);
	}
}
void Heap::create_heap_from_file()
{
	delete[] heap;
	string file_name;
	cout << "Enter file name: " << endl;
	cin >> file_name;

	fstream file;
	file.open(file_name.c_str(), ios::in);

	string size_of_heap;
	getline(file, size_of_heap);

	size = atoi(size_of_heap.c_str());
	cout << "Size frfom file: " << size << endl;

	for (int i = 0; i < size; i++)
	{
		string number_to_add;
		getline(file, number_to_add);
		number = atoi(number_to_add.c_str());
		add_element(number);
	}
	file.close();
}

void Heap::measure_time()
{
	
	const int NUMBER_OF_ITERATIONS = 2000;
	const int TAB_SIZE = 20;
	srand(time(NULL));
	int tab[TAB_SIZE];
	
	ofstream fout;
	fout.open("scores_heap.txt");
	

	for(int i=0;i<TAB_SIZE;i++){
		tab[i] = rand()%16;
	}

	for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
	{
		
		auto begin = chrono::steady_clock::now();

		for (int i = 0; i < TAB_SIZE; i++)
		{
			number = std::rand();
			add_element(tab[i]);
		}
		auto end = chrono::steady_clock::now();

		fout << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";
		
		begin = chrono::steady_clock::now();
		for (int i = 0; i < TAB_SIZE; i++)
		{
			delete_number(tab[i]);
		}
		end = chrono::steady_clock::now();
		fout << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << ";";	
		
		fout << "\n";
	}
	
	fout.close();
}

void Heap::menu_heap()
{
	const int n = 1000; // maksymalny rozmiar kopca
	int heap[n];

	int option = -1;
	string file_name;

	while (option != 0)
	{

		cout << "\nChoose option?" << endl;
		cout << "1. Load heap from file" << endl;
		cout << "2. Add element" << endl;
		cout << "3. Delete element" << endl;
		cout << "4. Check if heap contains number" << endl;
		cout << "5. Generate heap" << endl;
		cout << "6. Measure time" << endl;

		scanf("%i", &option);

		switch (option)
		{
		case 1:
		{
			create_heap_from_file();
		}
		break;
		case 2:
			cout << "Enter number to add: " << endl;
			cin >> number;
			add_element(number);
			break;
		case 3:
			cout << "Enter element to delete: " << endl;
			cin >> number;
			delete_number(number);
			break;
		case 4:
			cout << "Enter element to check: " << endl;
			cin >> number;
			find_element(number);
			break;
		case 5:
		{
			generate_heap();
		}
		break;
		case 6:
			measure_time();
			break;
		default:
			cout << "Enter correct option" << endl;
			Sleep(2000);
			break;
		}
		print_heap(heap, size);
	}
}