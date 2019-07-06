/** 
 * example to train construction-destruction processes and move semantics
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

		std::string&& get_root_name() const
		{
			return current->get_item_name();
		}

		std::shared_ptr<Todo> get_next() const
		{
			return next;
		}
	
};

void print(const TodoPair& t, std::string&& (TodoPair::*func)() const)
{
	std::cout << "item with name: " << (t.*func)() << std::endl;
}

void print(std::shared_ptr<Todo> p, std::string&& (Todo::*func)())
{
	// shared pointer operator->() returns pointer to object pointed by stored pointer
	// so we can use in the same way p.get() that returns contained pointer
	// then we can use *p to dereference contained object
	
	std::cout << "item with name: " << ((*p).*func)() << std::endl;
}


std::shared_ptr<Todo> construct()
{
	TodoPair t {"root", "child"};

	auto s = &TodoPair::get_root_name;
	auto ss = &Todo::get_item_name;

	print(t, s);
		
	auto p = t.get_next();

	print(p, ss);

	return p;

}



int main()
{
	std::cout << "start of main" << std::endl;
	
	std::shared_ptr<Todo> p = construct();
	
	std::cout << "end of main" << std::endl;

	//auto&& rp = t.get_next_move();
}

