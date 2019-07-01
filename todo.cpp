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
		Todo() : count{0}, item{"null"} 
		{
			std::cout << "constructor call for item without name" << std::endl;
		}
		
		Todo(std::string&& name) : count{0}, item{name} 
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
		Todo current;
		
		Todo next;

	public:		
		TodoList(std::string&& name) : TodoList(std::move(name), "null") {}
		
		TodoList(std::string&& name, std::string&& next_name) 
		
			: current(std::move(name)), next(std::move(next_name)) {}

		
		void set_item_name(std::string&& name)
		{
			current.set_item_name(std::move(name));
		}
		
		void set_next_name(std::string&& name)
		{
			std::cout << "next default name is: " << next.get_item_name() << std::endl;

			next.set_item_name(std::move(name));
		
			std::cout << "next name is: " << next.get_item_name() << std::endl;
		}

		std::string&& get_item_name()
		{
			return current.get_item_name();
		}

		Todo& get_next()
		{
			return next;
		}
	
		Todo&& get_next_move()
		{
			return std::move(next);
		}

};



int main()
{
	TodoList t {"root", "child"};
	
	auto& p = t.get_next();

	auto&& rp = t.get_next_move();
}

