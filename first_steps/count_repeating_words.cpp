#include <iostream> 
#include <string>
#include <unordered_map>
#include <fstream>
#include <iterator>
#include <unistd.h>
#include <limits>

//#include <vector>


/**
 * command to compile for windows with static libraries
 * i686-w64-mingw32-g++ -static-libgcc -static-libstdc++ count_repeating_words.cpp -o count_win.exe
 */

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


template <typename ForwardIterator, typename T>

void print_iterator(ForwardIterator begin, ForwardIterator end, std::forward_iterator_tag, T p)
{
	while(begin != end)
	{
		std::cout << *begin << std::endl;
		++begin;
	}
}


template <typename ForwardIterator, typename Key, typename Value>

void print_iterator(ForwardIterator begin, ForwardIterator end, std::forward_iterator_tag, std::pair<const Key, Value> p)
{
	while(begin != end)
	{
		std::cout << begin -> first << ":" << 
			     begin -> second << std::endl;
		++begin;
	}
}


template <typename Iterator> 

void print(Iterator begin, Iterator end)
{
	return print_iterator(begin, end, typename std::iterator_traits<Iterator>::iterator_category(), 
			typename std::iterator_traits<Iterator>::value_type());
}



template <typename T> 

bool fill_map(T& map, const std::string& file_path, void (*fn)(typename T::const_iterator, typename T::const_iterator))
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
			fn(map.cbegin(), map.cend());
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

typedef void (* callback_t) (umap::const_iterator, umap::const_iterator);


int main()
{
	umap map;

	callback_t prt = print;
	
	//std::vector<std::string> vec = { "one", "two", "three"};
	//print(vec.cbegin(), vec.cend());

	std::string file_name;
	
	if(read_file_name(file_name) && fill_map(map, file_name, prt))
	{
		std::cout << "programm terminated successfully" << std::endl;
	}
	else
	{
		std::cout << "programm terminated with errors" << std::endl;
	}	

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout <<"\npress enter to exit";
	std::getchar();
	
	return 0;
}
