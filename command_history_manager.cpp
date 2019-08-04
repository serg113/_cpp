#include <iostream>
#include <string>
#include <fstream>

namespace cmh
{

	class CommandHistoryManager
	{
		//std::string comlogfile;
		std::fstream comlog;

		public:
			CommandHistoryManager(){};

			CommandHistoryManager(std::string & file_path)
			{
				init(file_path);
			}
			~CommandHistoryManager()
			{

			}

			void open(std::string & file_path)
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

				return command;
			}
		private:
			void init(std::string & file)
			{
				comlog.open(file, std::fstream::in | std::fstream::out | std::fstream::app);
				
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
	
	std::cout << "write 3 commands below to save" << std::endl;

	for(int i = 0; i < 3; i++)
	{
		std::cin >> command;

		hist_manager.save_command(command);
	}

	for(int i = 0; i < 3; i++)
		std::cout << "previous command ~ " << hist_manager.get_prev_command() << std::endl;


}
