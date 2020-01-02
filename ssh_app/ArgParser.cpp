#include "ArgParser.h"

ArgParser::ArgParser() {};

bool ArgParser::ProcessArgs(const std::vector<std::string> & args)
{
	if (args.size() == 1)
	{
		if (args[0] == "-h" || args[0] == "--help") 
		{
			PrintHelp();
			return false;
		}
	}
	else if (args.size() == 3)
	{
		if (args[0] == "-rmcopy")
		{
			local_file_ = args[1];
			remote_file_ = args[2];

			std::replace(local_file_.begin(), local_file_.end(), '\\', '/');
			std::replace(remote_file_.begin(), remote_file_.end(), '\\', '/');

			return true;
		}			
	}
	
	PrintHelpHint();

	return false;
}

std::string ArgParser::get_source_path() const
{
	return local_file_;
}
std::string ArgParser::get_destination_path() const
{
	return remote_file_;
}

void ArgParser::PrintHelpHint() const
{
	std::cout << "\n>***< type -h or --help to see the list of available commands" << std::endl;
}

void ArgParser::PrintHelp() const
{
	std::cout << "\n>***< currently implemented commands:" << std::endl;
	std::cout << "---    ---   ---   ---" << std::endl;
	std::cout << "ssh_app.exe -rmcopy [source path] [destination path] " << std::endl;
}
