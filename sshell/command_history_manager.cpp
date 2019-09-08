#include "command_history_manager.h"

cmh::CommandHistoryManager::CommandHistoryManager(){};
cmh::CommandHistoryManager::CommandHistoryManager(const std::string& file_path)
{
	init(file_path);
}

cmh::CommandHistoryManager::~CommandHistoryManager()
{
	std::cout << "[cmh]: ~CommandHistoryManager()" << std::endl;
	save_history();
}

void cmh::CommandHistoryManager::open(const std::string& file_path)
{
	if(file_path != log_file)
		save_history();
	
	init(file_path);
}

void cmh::CommandHistoryManager::save_history()
{
	if(comlog.is_open())
	{
		std::cout << "[cmh]: save_history(), writing commands to file" 
			<< std::endl;
		for(auto command : prev_commands)
		{
			comlog << command << std::endl;

			std::cout << "written command: " 
				<< command << std::endl;
		}

		comlog.close();
	}

}

void cmh::CommandHistoryManager::save_command(const std::string& command)
{
	prev_commands.insert(prev_commands.begin(), command);
	prev_command = prev_commands.begin();
}


std::string cmh::CommandHistoryManager::get_prev_command()
{
	if(prev_commands.empty())
		return "";

	std::string ret_value = *prev_command;

	if(++prev_command == prev_commands.end())
		--prev_command;

	return ret_value;
}

void cmh::CommandHistoryManager::init(const std::string& file_path)
{
	//using comlog = cmh::CommandHistoryManager::comlog;
	cmh::CommandHistoryManager::log_file = file_path;
	if(!comlog.is_open())
		comlog.open(file_path, std::fstream::in | std::fstream::out);
	if(!comlog.is_open())
		comlog.open(file_path,
			std::fstream::in | std::fstream::out | std::fstream::trunc);
	std::string command;

	while(std::getline(comlog, command))
	{
		prev_commands.push_back(command);
	}
	prev_command = prev_commands.begin();

	comlog.clear();
	comlog.seekg(0);
}


