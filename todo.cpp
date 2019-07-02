/** 
 * to do list
 */

# include <iostream>
# include <string>
# include <vector>
# include <unistd.h>
# include <memory>
# include <utility>


class Todo
{
	private:
		int count;
		
		std::string item;
	public:
		
		Todo(std::string&& name = "null") : count{0}, item{name} 
		{
			std::cout << "constructor call for item: " << name << std::endl;
		}
		
		~Todo()
		{
			std::cout << "destructor call for item: " << item << std::endl;
		}

		void set_item_name(std::string&& name)
		{
			item = name;
			std::cout << "name of item changed to: " << item << std::endl;
		}

		std::string&& get_item_name()
		{
			return std::move(item);
		}
};

class TodoList
{
	private:
		Todo* current;
		
		Todo* next;

	public:		
		
		TodoList(std::string&& name = "null", std::string&& next_name = "null") 
		
			: current{new Todo{std::move(name)}}, next{new Todo{std::move(next_name)}} 
		{
			std::cout << "TodoList constructor call, parameters: " 
				  << name << ", " << next_name << std::endl;
		}

		~TodoList()
		{
			delete current;
			
			delete next;
		}

		std::string&& get_root_name()
		{
			return current->get_item_name();
		}

		Todo* get_next()
		{
			return next;
		}
	
};


void construct()
{
	//TodoList t0 {};
	//TodoList t1 {"root"};

	TodoList t {"root", "child"};

	std::cout << "first is item: " << t.get_root_name() << std::endl;
	
	auto* p = t.get_next();

	std::cout << "next is item: " << p->get_item_name() << std::endl;
}



int main()
{
	std::cout << "start of main" << std::endl;
	
	construct();
	
	std::cout << "end of main" << std::endl;

	//auto&& rp = t.get_next_move();
}

