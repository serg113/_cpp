#include "ArgParser.h"

ArgParser::ArgParser() {};

bool ArgParser::ProcessArgs(const std::vector<std::string> & args)
{
	if (args.size() == 1)
	{
		if (args[0] == "-h" || args[0] == "--help")
		{
			std::cout << "currently implemented commands: \n" << std::endl;
			std::cout << "ssh_app.exe -rmcopy [source path] [destination path] " << std::endl;
		}
		else
		{
			std::cout << "type -h or --help to see the list of available commands" << std::endl;
		}
	}
	else if (args.size() == 3)
	{
		if (args[0] == "-rmcopy")
		{
			local_file = args[1];
			remote_file = args[2];

			std::replace(local_file.begin(), local_file.end(), '\\', '/');
			std::replace(remote_file.begin(), remote_file.end(), '\\', '/');

			parsing_succeed = true;
		}
		else
		{
			std::cout << "type -h or --help to see the list of available commands" << std::endl;
		}
	}
	else
	{
		std::cout << "type -h or --help to see the list of available commands" << std::endl;
	}

	return parsing_succeed;
}

std::string ArgParser::get_source_path() const
{
	return local_file;
}
std::string ArgParser::get_destination_path() const
{
	return remote_file;
}
