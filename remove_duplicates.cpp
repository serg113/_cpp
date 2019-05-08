#include <iostream>
#include <unordered_set>

template <typename T>
std::unordered_set<T> array_to_set(const T * arr, const size_t sz)
{
	std::unordered_set<T> set;

	for(int i = 0; i != sz; i++)
	{
		set.insert(arr[i]);
	}

	return set;		
}


template <typename T> 
void convert_set_to_array(const std::unordered_set<T> set, T *arr)
{
	size_t sz = 0;

	for(T elm : set)
	{
		arr[sz] = elm;
		sz++;
	}
}



int main()
{
	int sz = 5;

	int input_array[sz] = {1, 2, 3, 2, 1};

	std::unordered_set<int> set = array_to_set(input_array, sz);
	
	int output_array[set.size()];
	
	convert_set_to_array(set, output_array);
	


	std::cout << "input array with duplicates: ";
	for(auto elm : input_array)
	{
		std::cout << elm << " ";
	}
	std::cout << std::endl;

	std::cout << "output array without duplicates: ";
	for(auto elm : output_array)
	{
		std::cout << elm << " ";
	}
	std::cout << std::endl;

	return 0;
}
