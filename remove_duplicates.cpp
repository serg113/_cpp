#include <iostream>
#include <unordered_set>
#include <initializer_list>
#include <list>
#include <iterator>
#include <vector>

template <typename Iterator, typename T>
class Filter
{	
	std::list<T> init_l;

	public:
		Filter() = delete; // force to initialize processing list at object construction
		
		Filter(const std::initializer_list<T>& list) : init_l { list }
		{
			std::cout << "constructor call --> initializer list" << std::endl;
		}

		Filter(const Iterator begin, const Iterator end)
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
		
		void init(const Iterator begin, const Iterator end, const std::forward_iterator_tag, const T)
		{
			init_l = std::list<T> { begin, end };
		}


		std::unordered_set<T> filter_duplicates_list() const
		{
			std::unordered_set<T> set(init_l.begin(), init_l.end());

			return set; //NRVO
		}
};


int main()
{
	/**
	 * initialization
	 */

	Filter<std::initializer_list<int>::iterator, int> filter_0 { 1, 3, 2, 1, 3};

	Filter<std::iterator<std::forward_iterator_tag, char>, char> filter_1{'a', 'b', 'c', 'a', 'c'};

	std::list<int> lst{1, 2, 3, 4, 3, 2, 1};
	
	Filter<std::list<int>::iterator, int> filter_2(lst.begin(), lst.end());

	/**
	 * filtering
	 */

	auto filter_0_set = filter_0.get_without_duplicates();	

	auto filter_1_set = filter_1.get_without_duplicates();
		
	auto filter_2_set = filter_2.get_without_duplicates();

	/**
	 * printing
	 */

	for(auto i : filter_0_set) { std::cout << i << " ";} std::cout << std::endl;

	for(auto i : filter_1_set) { std::cout << i << " ";} std::cout << std::endl;
	
	for(auto i : filter_2_set) { std::cout << i << " "; } std::cout << std::endl;
	
}
