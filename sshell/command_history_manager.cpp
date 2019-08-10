#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>

namespace cmh
{
	/**
	 * todo: priority:
	 *    
	 *    2. 	1. limit commands count to 10
	 * 	
	 */

	class CommandHistoryManager
	{
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
				std::cout << "[cmh]: ~CommnadHistoryManager()" << std::endl;
			
				save_history();
			}

			void open(const std::string & file_path)
			{
				if(file_path != log_file)
					save_history();

				init(file_path);
			}

			void save_history()
			{
				if(comlog.is_open())
				{
					std::cout << "[cmh]: save_history(), writing commands to file" << std::endl;

					for(auto command : prev_commands)
					{
						comlog << command << std::endl;

						std::cout << "written command: " << command << std::endl;
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
				if(prev_commands.empty())
					return "";

				std::string ret_value = *prev_command;

				if(++prev_command == prev_commands.end())  
					--prev_command;

				return ret_value;
			}

		private:
			void init(const std::string & file_path)
			{
				log_file = file_path;

				if(!comlog.is_open())
					comlog.open(file_path, std::fstream::in | std::fstream::out);

				if(!comlog.is_open())
					comlog.open(file_path, std::fstream::in | std::fstream::out | std::fstream::trunc);
				
				std::string command;

				while(std::getline(comlog, command))
				{
					prev_commands.push_back(command);
				}
				prev_command = prev_commands.begin();		

				comlog.clear();	
				comlog.seekg(0);
			}
	};
}

int main()
{
	std::string file = "command.log";

	cmh::CommandHistoryManager m_history(file);


	std::cout << "last three commands: ";
	for(int i = 0; i < 3; i++)
		std::cout << m_history.get_prev_command() << " >>> ";
	std::cout << std::endl << std::endl;


	std::string command;

	for(int i = 0; i < 2; ++i)
	{
	
		std::cout << "write command here: ";

		std::cin >> command;

		m_history.save_command(command);
	
		std::cout << "previous command was: " << m_history.get_prev_command() << std::endl;
	}

}
