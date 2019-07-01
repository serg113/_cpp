/* 
the purpose of writing this code 
is for finding answer for raised question.

is auto specifier calls object destructor after it's use?

*/

# include <iostream>
# include <string>
# include <vector>
# include <unistd.h>
# include <memory>
# include <utility>


class Node
{
	private:
		int count;
		std::string item;
	public:
		Node() : count{0}, item{"null"} 
		{
			std::cout << "constructor called for item without name" << std::endl;
		}
		
		Node(std::string& name) : count{0}, item{name} 
		{
			std::cout << "constructor called with item name: " << name << std::endl;
		}
		
		~Node()
		{
			std::cout << "destructor colled for item: " << item << std::endl;
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

class NodeList
{
	Node current;
	Node next;

public:

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

	Node& get_next()
	{
		// call this function with auto specifier make one more destructor call
		return next;
	}
	
	Node&& get_next_move()
	{
		// the same as above, more destructor calls with auto
		return std::move(next);
	}

};



int main()
{

	NodeList t;
		
	t.set_item_name("root");
	t.set_next_name("child");	

	Node& p = t.get_next();
  
	// check why auto makes additional call to destructor, without calling constructor
	//std::cout << "created item with name: " << p.get_item_name() << std::endl;
	
	//Node&& rp = t.get_next_move();
	//std::cout << "move object value: " << rp.get_item_name() << std::endl;

}
