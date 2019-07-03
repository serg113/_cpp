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

class TodoList
{
	private:
		
		std::shared_ptr<Todo> current; 
		
		std::shared_ptr<Todo> next;

	public:		
		
		TodoList(const std::string&& name = "null", const std::string&& next_name = "null") 
		
			//: current{new Todo{std::move(name)}}, next{new Todo{std::move(next_name)}} 
		{
			std::cout << "TodoList constructor was called, parameters: " 
				  << name << ", " << next_name << std::endl;
			
			current = std::make_shared<Todo>(std::move(name));

			next = std::make_shared<Todo>(std::move(next_name));
		}

		~TodoList(){}

		std::string&& get_root_name() const
		{
			return current->get_item_name();
		}

		std::shared_ptr<Todo> get_next() const
		{
			return next;
		}
	
};


std::shared_ptr<Todo> construct()
{
	//TodoList t0 {};
	//TodoList t1 {"root"};

	TodoList t {"root", "child"};

	std::cout << "first is item: " << t.get_root_name() << std::endl;
	
	auto p = t.get_next();

	std::cout << "next is item: " << p->get_item_name() << std::endl;

	return p;

}



int main()
{
	std::cout << "start of main" << std::endl;
	
	std::shared_ptr<Todo> p = construct();

	std::cout << "getting shared pointer from main for item: " << p->get_item_name() << std::endl;
	
	std::cout << "end of main" << std::endl;

	//auto&& rp = t.get_next_move();
}

