#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

typedef struct {
	size_t comparison_count;
	size_t copy_count;
} stats;

//const int n = 1000;

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
	srand(time(NULL));
	int otf = 0;
	int type_sort = 0;
	while (type_sort <= 1)
	{
		int otf = 0;
		while (otf <= 2)
		{
			int n = 1000;
			while (n <= 10000)
			{
				vector <int> data(n);
				stats avg_stats = { 0 };
				for (int k = 0; k < 100; k++)
				{
					if (otf == 0)
					{
						for (int i = 0; i < n; i++) data[i] = rand() % 100;
					}
					if (otf == 1)
					{
						for (int i = 0; i < n; i++) data[i] = i; ;
					}
					if (otf == 2)
					{
						for (int i = 0; i < n; i++) data[i] = n - i;;
					}

					stats data_stats = { 0 }; // объявили статистику
					if (type_sort == 0) data_stats = selection_sort(data);
					if (type_sort == 1) data_stats = quick_sort(data);
					avg_stats.comparison_count += data_stats.comparison_count;
					avg_stats.copy_count += data_stats.copy_count;
				}
				if (type_sort == 0) cout << "Вставками: " << endl;
				if (type_sort == 1) cout << "Быстрая: " << endl;
				if (otf == 0) cout << "Рандом: " << endl;
				if (otf == 1) cout << "Прямой порядок: " << endl;
				if (otf == 2) cout << "Обратный порядок: " << endl;
				cout << "Размерность массива: " << n << endl;
				cout << "Количество сравнений: " << avg_stats.comparison_count / 100 << endl;
				cout << "Количество обменов: " << avg_stats.copy_count / 100 << endl;
				cout << "______________________________ " << endl;
				n = n + 1000;
			}
			otf++;;
		}
		type_sort++;
	}
	system("pause");
}
