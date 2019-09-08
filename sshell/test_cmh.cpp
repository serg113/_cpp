# include <string>
# include "command_history_manager.h"

// compile: g++ -o test_h test_cmh.cpp command_history_manager.cpp 

int main()
{
	std::string log_file = "command.log";

	cmh::CommandHistoryManager m_command(log_file);

	std::cout << "last three commands: ";
	for(int i = 0; i < 3; i++)
		std::cout << m_command.get_prev_command() << " >>> ";
	std::cout << std::endl << std::endl;

	std::string cmd;

	for(int i = 0; i < 2; i++)
	{
		std::cout << "write command here: ";

		std::cin >> cmd;

		m_command.save_command(cmd);

		std::cout << "previous command was: " <<
			m_command.get_prev_command() << std::endl;
	}
}




