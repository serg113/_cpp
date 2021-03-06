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


class TodoBase
{
	public:
		virtual const std::string& get_item_name() const = 0;
};


class Todo : public TodoBase
{
	private:

		int count;
		
		std::string item_name;
	public:
		
		Todo(const Todo& t)
		{
			std::cout << "---> copy constructor call: " << t.get_item_name() << std::endl;

			item_name = t.get_item_name();
		}

		Todo(Todo&& t)
		{
			std::cout << "---> move constructor call: " << t.get_item_name() << std::endl;
			item_name = t.get_item_name();
		}

		Todo(const std::string&& name = "null") : count{0}, item_name{name} 
		{
			std::cout << "---> constructor call for item: " << name << std::endl;
		}
		
		~Todo()
		{
			std::cout << "---< destructor call for item: " << item_name << std::endl;
		}

		void set_item_name(const std::string&& name)
		{
			item_name = name;
			std::cout << "name of item changed to: " << item_name << std::endl;
		}
		
		const std::string& get_item_name() const
		{
			return item_name;
		}
};

class TodoPair 
{
	private:
		
		std::shared_ptr<Todo> current; 
		
		std::shared_ptr<Todo> next;

	public:		
	
		TodoPair(const std::string name = "null", const std::string next_name = "null") 	
		{
			std::cout << "---> TodoPair constructor called, parameters: " << name << ", " << next_name << std::endl;
			
			current = std::make_shared<Todo>(std::move(name));

			next = std::make_shared<Todo>(std::move(next_name));
		}

		~TodoPair(){}

		const std::string& get_current_name() const
		{
			return current->get_item_name();
		}

		const std::string& get_next_name() const
		{
			return next->get_item_name();
		}

		std::shared_ptr<Todo> get_next() const
		{
			return next;
		}
	
};

void print(const TodoPair& pair_item, const std::string& (TodoPair::*func)() const)
{
	std::cout << "item with name: " << (pair_item.*func)() << std::endl;
}

void print(std::shared_ptr<Todo> item_ptr, const std::string& (TodoBase::*func)() const)
{
	// shared pointer operator->() returns pointer to object pointed by stored pointer
	// so we can use in the same way p.get() that returns contained pointer
	// then we can use *p to dereference contained object
	
	std::cout << "item with name: " << ((*item_ptr).*func)() << std::endl;
}


typedef const std::string& (TodoPair::*f_ptr)() const;


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
	
	auto td_fptr = &TodoBase::get_item_name;
	
	print(pair, tp_fptr);
	
	print(item, td_fptr);
		
	//collecting function pointers in array

	std::list<f_ptr> f_list {&TodoPair::get_current_name, &TodoPair::get_next_name};	
	
	print(pair, f_list);

	return item;
}



int main()
{
	std::cout << "start of main" << std::endl;
	
	auto item = construct();
	
	std::cout << "end of main\n --- still alive item: " << item->get_item_name() << std::endl;
}

