#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>

namespace cmh
{
	/**
	 * todo:
	 * 	1. limit commands count to 10
	 * 	
	 */

	class CommandHistoryManager
	{
		public:
			bool end_of_log {false};
		
		private:
			std::string log_file;
		
			std::fstream comlog;
			std::list<std::string> prev_commands;
			std::list<std::string>::iterator prev_command = prev_commands.begin();
			

		public:
			CommandHistoryManager(){};

			CommandHistoryManager(const std::string & file_path)
			{
				init(file_path);
			}
			
			~CommandHistoryManager()
			{
				close();
				
				std::cout << "~CommnadHistoryManager(): comlog->closed" << std::endl;
			}

			void open(const std::string & file_path)
			{
				init(file_path);
			}

			void close()
			{
				if(comlog.is_open())
				{
					for(auto command : prev_commands)
					{
						comlog << command << std::endl;

						std::cout << "written row: " << command << std::endl;
					}
					comlog.close();
				}
			}

			void save_command(const std::string & command)
			{
				prev_commands.insert(prev_commands.begin(), command);
				
				prev_command = prev_commands.begin();
			}

			std::string get_prev_command()
			{
				if(std::distance(prev_command, prev_commands.end()))
					return *(prev_command++);
				else
					return "";
			}

		private:
			void init(const std::string & file_path)
			{
				if(!comlog.is_open())
					comlog.open(file_path, std::fstream::in | std::fstream::out);

				if(!comlog.is_open())
					comlog.open(file_path, std::fstream::in | std::fstream::out | std::fstream::trunc);
				
				std::string command;

				while(comlog.is_open() && std::getline(comlog, command))
				{
					prev_commands.push_back(command);
					prev_command = prev_commands.begin();
				}		

				comlog.clear();	
				comlog.seekg(0);
			}
	};
}

int main()
{
	std::string file = "command.log";

	cmh::CommandHistoryManager hist_manager;

	try{
		hist_manager.open(file);
	}
	catch(const char* msg){
		std::cerr << msg << std::endl;	
	}

	for(int i = 0; i < 3; i++)
		
		std::cout << "is in last three commands: " << hist_manager.get_prev_command() << std::endl;


	std::string command;

	for(int i = 0; i < 2; ++i)
	{
	
		std::cout << "write command here: ";

		std::cin >> command;

		hist_manager.save_command(command);
	
		std::cout << "previous command was: " << hist_manager.get_prev_command() << std::endl;
	}
	hist_manager.close();

	/*while(!hist_manager.end_of_log)
	{
		std::cout << "written command ~/ " << hist_manager.get_prev_command() << std::endl;
	}*/

}