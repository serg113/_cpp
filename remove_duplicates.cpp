#include <iostream>
#include <unordered_set>
#include <initializer_list>
#include <list>
#include <iterator>
#include <vector>

template <typename T>
class Filter
{

	typedef typename std::vector<T>::const_iterator it_v;
	typedef typename std::list<T>::const_iterator it_l;

	std::unordered_set<T> (Filter<T>::*filter_dupl)() const;	
	
	std::vector<T> vec_org;
	std::list<T> list_org;

	public:
		Filter() = delete;
		
		Filter(std::initializer_list<T> list)
		{
			std::cout << "constactor call --> initializer list" << std::endl;

			for(auto& item : list) // may be initialized without loop ???
			{
				list_org.push_back(item);
			}
		
			filter_dupl = &Filter<T>::filter_duplicates_list;
		}
		
		Filter(it_v begin, it_v end)
		{
			std::cout << "constructor call --> vector iterator case" << std::endl;

			for(auto it = begin; it != end; it++)
			{
				vec_org.push_back(*it);
			}
			
			this->filter_dupl = &Filter<T>::filter_duplicates_vector;
		}

		Filter(it_l begin, it_l end)
		{
			std::cout << "constructor call --> list iterator case" << std::endl;

			for(auto it = begin; it != end; it++)
			{
				list_org.push_back(*it);
			}
	
			this->filter_dupl = &Filter::filter_duplicates_list;
		}

		std::unordered_set<T> get_without_duplicates() const
		{
			return (this->*filter_dupl)();
		}

	private:

		std::unordered_set<T> filter_duplicates_list() const
		{
			std::unordered_set<T> set;

			for(auto& item : list_org)
			{
				set.insert(item);
			}

			return set;
		}

		std::unordered_set<T> filter_duplicates_vector() const
		{
			std::unordered_set<T> set;

			for(auto& item : vec_org)
			{
				set.insert(item);
			}

			return set;
		}


};


int main()
{
	Filter<char> filter{'a', 'b', 'c', 'a', 'c'};
	
	auto char_set = filter.get_without_duplicates();

	for(auto i : char_set) 
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;


	std::list<int> vec{1, 2, 3, 4, 3, 2, 1};
	
	Filter<int> filt(vec.cbegin(), vec.cend());

	auto int_set = filt.get_without_duplicates();
	
	for(auto i : int_set)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
