#include <iostream> 
#include <string>
#include <unordered_map>
#include <fstream>
#include <iterator>
#include <unistd.h>



bool read_file_name(std::string& file_name)
{
	bool success = true;

	std::cout << "input file path for processing: ";

	std::cin >> file_name;

	if(access(file_name.c_str(), R_OK ) == -1)
	{
		std::cout << "error: file doesnot exist or permission denied, path: " << file_name << std::endl;

		success = false;
	}
	
	return success;
}



template <typename ForwardIterator>

void _print_map(ForwardIterator begin, ForwardIterator end, std::forward_iterator_tag)
{
	for(; begin != end; begin++)
	{
		std::cout << begin -> first << ":" << begin -> second << std::endl;
	}
}


template <typename Iterator> 

void print_map(Iterator begin, Iterator end)
{
	return _print_map(begin, end, typename std::iterator_traits<Iterator>::iterator_category());
}


template <typename T> 

bool fill_map(T& map, const std::string& file_path, void (*fn)(typename T::iterator, typename T::iterator))
{
	bool success;

	std::ifstream file(file_path);
	
	std::string word;

	if(file.is_open())
	{
		std::cout << "ok: file opened: " << file_path << std::endl;

		while(file >> word)
		{
			map[word] += 1;
		}
	
		file.close();
	
		if(fn != nullptr)
		{
			fn(map.begin(), map.end());
		}
		else { std::cout << "error: null pointer for callback function" << std::endl;}

		success = true;
	}
	else
	{
		std::cout << "error: cannot open the file: " << file_path << std::endl;

		success = false;
	}

	return success;
}



typedef std::unordered_map<std::string, int> umap;

typedef void (* callback_t) (umap::iterator, umap::iterator);


int main()
{
	umap map;

	callback_t prt = print_map;

	std::string file_name;
	
	if(read_file_name(file_name) && fill_map(map, file_name, prt))
	{
		std::cout << "programm terminated successfully" << std::endl;
	}
	else
	{
		std::cout << "programm terminated with errors" << std::endl;
	}	

	return 0;
}
