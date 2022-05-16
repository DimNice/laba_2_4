#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

typedef struct {
	size_t comparison_count;
	size_t copy_count;
} stats;

const int n = 1000;

stats selection_sort(std::vector<int>& data) 
{
	int count, key;
	stats current_stats = { 0 };
	for (unsigned int i = 0; i < data.size() - 1; i++)
	{
		count = data[i];
		key = i;
		for (unsigned int j = i + 1; j < data.size(); j++)
		{
			current_stats.comparison_count++; // увеличиваем счётчик сравнений
			if (data[j] < data[key])
				key = j;
		}
		current_stats.comparison_count++; // увеличиваем счётчик сравнений
		if (key != i)
		{
			current_stats.copy_count++;  // увеличиваем счётчик присваиваний
			data[i] = data[key];
			data[key] = count;
		}
	}

	return current_stats;
}

void quicksort(std::vector<int>& data, int first, int last, size_t& comp_count, size_t& copy_count)
{
	int mid, count;
	int f = first, l = last;
	mid = data[(f + l) / 2]; //вычисление опорного элемента
	do
	{
		while (data[f] < mid)
			f++;
		while (data[l] > mid)
			l--;
		comp_count++; // увеличиваем счётчик сравнений
		if (f <= l) //перестановка элементов
		{
			copy_count++;  // увеличиваем счётчик присваиваний
			count = data[f];
			data[f] = data[l];
			data[l] = count;
			f++;
			l--;
		}
	} while (f < l);

	if (first < l)
		quicksort(data, first, l, comp_count, copy_count);
	if (f < last)
		quicksort(data, f, last, comp_count, copy_count);
}

stats quick_sort(std::vector<int>& data)
{
	stats current_stats = { 0 };
	quicksort(data, 0, data.size() - 1, current_stats.comparison_count, current_stats.copy_count);

	return current_stats;
}

void main()
{
	setlocale(LC_ALL, "Rus");
	vector <int> data(n);
	srand(time(NULL));
	stats avg_stats = { 0 };
	for (int k = 0; k < 100; k++) 
	{
		for (int i = 0; i < n; i++)
		{
			data[i] = rand() % 100; 
			//data[i] = i; 
			//data[i] = n - i; 
			//cout << data[i] << " ";
		}

		stats data_stats = { 0 }; // объявили статистику
		data_stats = selection_sort(data);
		//data_stats = quick_sort(data);
		avg_stats.comparison_count += data_stats.comparison_count;
		avg_stats.copy_count += data_stats.copy_count;
		//cout<<endl<<"Результирующий массив: ";
		//for (int i = 0; i < n; i++)
		//	cout << data[i] << " ";
	}
	cout << endl << "Количество сравнений: " << avg_stats.comparison_count / 100 << endl;
	cout << "Количество обменов: " << avg_stats.copy_count / 100 << endl;
	system("pause");
}
