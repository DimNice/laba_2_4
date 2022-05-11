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
void main()
{
	vector <int> data(n);
	srand(time(NULL));
	stats avg_stats = { 0 };
	for (int k = 0; k < 100; k++) 
	{
		for (int i = 0; i < n; i++)
		{
			data[i] = rand() % 100; 
			//cout << data[i] << " ";
		}

		stats data_stats = { 0 }; 
		data_stats = selection_sort(data);
		avg_stats.comparison_count += data_stats.comparison_count;
		avg_stats.copy_count += data_stats.copy_count;
		//cout<<endl<<"result: ";
		//for (int i = 0; i < n; i++)
		//	cout << data[i] << " ";
	}
	cout << endl << "comparison_count: " << avg_stats.comparison_count  << endl;
	cout << "copy_count: " << avg_stats.copy_count  << endl;
	system("pause");
}