/** 
 * example to train construction-destruction processes, move semantics, and callback functions
 */

# include <iostream>
# include <string>
# include <vector>
# include <unistd.h>
# include <memory>
# include <utility>
# include <list>


class Base
{
	public:
		virtual std::string&& get_item_name() = 0;
};


class Todo : public Base
{
	private:

		int count;
		
		std::string item_name;
	public:
		
		Todo(const std::string&& name = "null") : count{0}, item_name{name} 
		{
			std::cout << "constructor call for item: " << name << std::endl;
		}
		
		~Todo()
		{
			std::cout << "destructor call for item: " << item_name << std::endl;
		}

		void set_item_name(const std::string&& name)
		{
			item_name = name;
			std::cout << "name of item changed to: " << item_name << std::endl;
		}
		
		std::string&& get_item_name()
		{
			return std::move(item_name);
		}
};

class TodoPair 
{
	private:
		
		std::shared_ptr<Todo> current; 
		
		std::shared_ptr<Todo> next;

	public:		
		
		TodoPair(const std::string&& name = "null", const std::string&& next_name = "null") 
		
			//: current{new Todo{std::move(name)}}, next{new Todo{std::move(next_name)}} 
		{
			std::cout << "TodoPair constructor was called, parameters: " 
				  << name << ", " << next_name << std::endl;
			
			current = std::make_shared<Todo>(std::move(name));

			next = std::make_shared<Todo>(std::move(next_name));
		}

		~TodoPair(){}

		std::string&& get_current_name() const
		{
			return current->get_item_name();
		}

		std::string&& get_next_name() const
		{
			return next->get_item_name();
		}

		std::shared_ptr<Todo> get_next() const
		{
			return next;
		}
	
};

void print(const TodoPair& pair_item, std::string&& (TodoPair::*func)() const)
{
	std::cout << "item with name: " << (pair_item.*func)() << std::endl;
}

void print(std::shared_ptr<Todo> item_ptr, std::string&& (Todo::*func)())
{
	// shared pointer operator->() returns pointer to object pointed by stored pointer
	// so we can use in the same way p.get() that returns contained pointer
	// then we can use *p to dereference contained object
	
	std::cout << "item with name: " << ((*item_ptr).*func)() << std::endl;
}


typedef std::string&& (TodoPair::*f_ptr)() const;


void print(const TodoPair& tp_ptr, const std::list<f_ptr> f_list)
{
	std::cout << "start of printing list of pointers" << std::endl;

	for(auto f : f_list)
	{
		std::cout << "item name: " << (tp_ptr.*f)() << std::endl;
	}

	std::cout << "end of printing list of pointers" << std::endl;	
}


std::shared_ptr<Todo> construct()
{
	TodoPair pair {"root", "child"};
	
	std::shared_ptr<Todo> item = pair.get_next();

	auto tp_fptr = &TodoPair::get_current_name;
	
	auto td_fptr = &Todo::get_item_name;
	
	print(pair, tp_fptr);
	
	print(item, td_fptr);
		
	//collecting all functions in one array

	std::list<f_ptr> f_list {&TodoPair::get_current_name, &TodoPair::get_next_name};	
	
	print(pair, f_list);

	return item;
}



int main()
{
	std::cout << "start of main" << std::endl;
	
	std::shared_ptr<Todo> item = construct();
	
	std::cout << "end of main" << std::endl;
}

