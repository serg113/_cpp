#include <iostream>
#include <unordered_set>
#include <initializer_list>
#include <list>
#include <iterator>
#include <vector>

template <typename T, typename Iterator>
class Filter
{	
	std::list<T> list_init;

	public:
		Filter() = delete; // force to initialize processing list at object construction
		
		Filter(const std::initializer_list<T>& list) : list_init { list }
		{
			std::cout << "constactor call --> initializer list" << std::endl;
		}

		Filter(Iterator begin, Iterator end)
		{
			std::cout << "constructor call --> iterators" << std::endl;

			init(begin, end, 
				typename std::iterator_traits<Iterator>::iterator_category(), 
					typename std::iterator_traits<Iterator>::value_type());
		}
	
		std::unordered_set<T> get_without_duplicates() const
		{
			return filter_duplicates_list();
		}


	private:
		
		void init(Iterator begin, Iterator end, std::forward_iterator_tag, T)
		{
			list_init = std::list<T>{begin, end};
		}


		std::unordered_set<T> filter_duplicates_list() const
		{
			std::unordered_set<T> set(list_init.begin(), list_init.end());

			return set; //NRVO
		}
};


int main()
{
	/**
	 * initialization
	 */

	Filter<int, std::initializer_list<int>::iterator> filter_0 { 1, 3, 2, 1, 3};

	Filter<char, std::iterator<std::forward_iterator_tag, char> > filter{'a', 'b', 'c', 'a', 'c'};

	std::list<int> lst{1, 2, 3, 4, 3, 2, 1};
	
	Filter<int, std::list<int>::iterator> filter_2(lst.begin(), lst.end());

	/**
	 * filtering
	 */

	auto filter_0_set = filter_0.get_without_duplicates();	

	auto filter_set = filter.get_without_duplicates();
		
	auto filter_2_set = filter_2.get_without_duplicates();

	/**
	 * printing
	 */

	for(auto i : filter_0_set) { std::cout << i << " ";} std::cout << std::endl;

	for(auto i : filter_set) { std::cout << i << " ";} std::cout << std::endl;
	
	for(auto i : filter_2_set) { std::cout << i << " "; } std::cout << std::endl;
	
}
