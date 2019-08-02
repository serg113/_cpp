# include <iostream>
# include <list>
# include <unordered_set>

/**
 * this function removes duplicates in list of items
 * based on comparator, like structuring bynary tree, 
 * so output values are sorted in ascending order
 */

template <typename T>
std::list<T> remove_duplicates(std::list<T> & lst)
{
	std::list<T> r_values;

	for(auto item : lst)
	{
		std::cout << "steps for item: " << item << std::endl;
		
		int count = 0;

		if(r_values.begin() == r_values.end() || item > *(--r_values.end()))
		{
			r_values.push_back(item);

			std::cout << "push back: " << item << ", steps: " << count << std::endl;
		}
		else if(item < *r_values.begin())
		{
			std::cout << " begin of list --> " << *r_values.begin() << std::endl;
			r_values.insert(r_values.begin(), item);

			std::cout << "insert at front: " << item << " steps: " << count << std::endl;
		}
		else
		{
		
			auto it_begin = r_values.begin();
			auto it_end = r_values.end();


			while(true)
			{ 
				++count;
				
				auto it = it_begin;
				
				int distance = std::distance(it_begin, it_end);
				
				int advance_step = distance/2;

				std::advance(it, advance_step);

				if(item < *it)
				{
					if(advance_step == 0 || advance_step == 1)
					{
						if(item > *it_begin)
						{
							r_values.insert(it, item);
							std::cout << "insert: " << item << ", steps: " << count << std::endl;
							break;
						}
						else
						{
							std::cout << "duplicate: " << item << ", steps: " << count << std::endl;
							break;
						}
					}
					else
					{
						it_end = ++it;
					}
				}
				else if(item > *it)
				{
					if(advance_step == 0 || advance_step == 1)
					{
						r_values.insert(--it_end, item);
						std::cout << "insert after: " << item << ", steps: " << count << std::endl;
						break;
					}
					else
					{
						it_begin = it;
					}
				}	
				else
				{
					std::cout << "not added: " << item << ", steps: "<< count << std::endl;
					break;
				}
			}
		}
	}

	return r_values;
}

template < typename T> 
void print_list(std::list<T> & lst)
{
	for(auto i : lst)
		std::cout << i << " ";
	std::cout << std::endl;
}

int main()
{
	std::cout << "*** start_s_s ***" << std::endl;
	
	std::list<int> lst { 1, 5, 3, 4, 3, 2, 1, 9, 0, 10, 15, 20, 7, 6, 30, 7, 20, 12, 1, 5, 9, 13, 11, 17, 22 };
	print_list(lst);

	//std::unordered_set<int> set(lst.begin(), lst.end());
	auto set = remove_duplicates(lst);

	print_list(set);
}
