# include <iostream> 
# include <string>
# include <fstream>
# include <list>
# include <iterator>

#ifndef COMMAND_H
#define COMMAND_H

namespace cmh
{
	class CommandHistoryManager
	{
		public:
			CommandHistoryManager();
			CommandHistoryManager(const std::string& file_path);
			~CommandHistoryManager();

			void open(const std::string& file_path);
			void save_history();
			void save_command(const std::string& command);
			std::string get_prev_command();
		private:
			std::string log_file;
			std::fstream comlog;
			std::list<std::string> prev_commands;
			std::list<std::string>::iterator prev_command;
			void init(const std::string& file_path);
	};
}


#endif
