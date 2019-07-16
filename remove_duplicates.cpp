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
		Filter() = delete;
		
		Filter(const std::initializer_list<T>& list) : list_init { list }
		{
			std::cout << "constactor call --> initializer list" << std::endl;
		}

		Filter(const Iterator begin, const  Iterator end)
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
	
		void init(const Iterator begin, const Iterator end, std::forward_iterator_tag, T)
		{
			for(auto it = begin; it != end; it++)
			{
				list_init.push_back(*it);
			}
		}


		std::unordered_set<T> filter_duplicates_list() const
		{
			std::unordered_set<T> set;

			for(auto& item : list_init)
			{	
				set.insert(item);
			}
			return set; //NRVO
		}
};


int main()
{
	Filter<char, std::iterator<std::forward_iterator_tag, char> > filter{'a', 'b', 'c', 'a', 'c'};
	
	auto char_set = filter.get_without_duplicates();

	
	for(auto i : char_set) { std::cout << i << " ";} std::cout << std::endl;


	
	std::list<int> lst{1, 2, 3, 4, 3, 2, 1};
	
	Filter<int, std::list<int>::iterator> filter_2(lst.begin(), lst.end());

	auto int_set = filter_2.get_without_duplicates();

	
	for(auto i : int_set) { std::cout << i << " "; } std::cout << std::endl;
	
}
