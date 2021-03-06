# include <iostream>
# include <list>


/**
 * this function removes duplicates from list of items
 * based on "<" comparator, like structuring bynary tree, 
 * so output values are sorted in ascending order
 *
 * issues:
 * 
 * 1. sorting algorithms are based on random access iterators, 
 * 	reason became clear for me after I try to sort std::list here
 * 	the std::advance function needs to take O(n/2) time to access middle of array, 
 * 	
 * 	in case of random access iterator it will take constant time, 
 * 	but insertion (in std::vector) will take linear time, 
 *
 * 	so complexity of current approach can be derived:
 *	1. there are N elements in array, so at first we iterate an array that is O(N) - linear time complexity
 *	2. then we insert an element to list each element in O(log(N)) steps
 *	3. at each insertion iterator need to std::advance(it, x), where x decrease as O(log(N))
 *
 *	so if I count in the right way, we have N*log(N)*log(N) complexity
 * 	
 * 2.
 *
 *
 */

template <typename T>
std::list<T> remove_duplicates(std::list<T> & lst)
{
	std::list<T> res;

	for(auto item : lst)
	{
		std::cout << "steps for item: " << item << std::endl;
		
		int count = 0;
		bool is_inserted {false};


		if(res.begin() == res.end() || *(--res.end()) < item)
		{
			res.push_back(item);

			is_inserted = true;
			std::cout << "pushed back: " << item << ", steps: " << count << std::endl;
		}
		
		if(!is_inserted && item < *res.begin())
		{
			res.insert(res.begin(), item);

			is_inserted = true;
			std::cout << "inserted at front: " << item << " steps: " << count << std::endl;
		}
		
		auto it_begin = res.begin();
		auto it_end = res.end();

		while(!is_inserted)
		{ 
			++count;
				
			auto it = it_begin;
				
			int half_len = std::distance(it_begin, it_end) / 2;
			
			std::advance(it, half_len);

			if(item < *it)
			{
				if(half_len < 1)
				{
					res.insert(it, item);
					is_inserted = true;
				}
				else
				{
					it_end = it;
				}
			}
			else if(*it < item)
			{
				if(half_len < 1)
				{
					res.insert(++it, item);
					is_inserted = true;
				}
				else
				{
					it_begin = it;
				}
			}	
			else
			{
				std::cout << "<<!!!>> duplicate: " << item << ", steps: "<< count << std::endl;
				break;
			}

			if(is_inserted)
				std::cout << "inserted item: " << item << ", steps: " << count << std::endl;
				
		}
	}

	return res;
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

	auto filtered = remove_duplicates(lst);

	print_list(lst);
	print_list(filtered);
}
