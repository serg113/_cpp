#include <iostream>
#include <string>
#include <fstream>

namespace cmh
{
	/**
	 * todo: 
	 * 	1. limit commands count to 10
	 * 	2. get commands in reversed order
	 */

	class CommandHistoryManager
	{
		public:
			bool end_of_log {false};

		private:
		
			std::fstream comlog;


		public:
			CommandHistoryManager(){};

			CommandHistoryManager(const std::string & file_path)
			{
				init(file_path);
			}
			
			~CommandHistoryManager()
			{
				comlog.close();
				
				std::cout << "~CommnadHistoryManager(): comlog->closed" << std::endl;
			}

			void open(const std::string & file_path)
			{
				init(file_path);
			}

			void save_command(const std::string & command)
			{
				if(!comlog.is_open()) throw "[write error]";

				comlog << command << std::endl;
				
				comlog.seekg(0);
			}

			std::string get_prev_command()
			{
				if(!comlog.is_open()) throw "[read error]";
				
				std::string command;
				
				std::getline(comlog, command);
				
				if(comlog.eof()==1) 
				{
					std::cout << "[end of file]" << std::endl;
					end_of_log = true;
				}

				return command;
			}
		private:
			void init(const std::string & file_path)
			{
				comlog.open(file_path, std::fstream::in | std::fstream::out | std::fstream::app);
				
				if(!comlog.is_open()) throw "[init error]";
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

	std::string command;
	
	std::cout << "write command here ~/ ";

	std::cin >> command;

	hist_manager.save_command(command);

	while(!hist_manager.end_of_log)
	{
		std::cout << "written command ~/ " << hist_manager.get_prev_command() << std::endl;
	}

}
