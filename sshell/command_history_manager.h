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
			CommandHistoryManager(const std::string&);
			~CommandHistoryManager();

			void open(const std::string&);
			void save_history();
			void save_command(const std::string&);
			std::string get_prev_command();
		private:
			std::string log_file;
			std::fstream comlog;
			std::list<std::string> prev_commands;
			std::list<std::string>::iterator prev_command;
			void init(const std::string&);
	};
}


#endif
