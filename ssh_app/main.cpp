//#include <sys/stat.h>
#include <fcntl.h>
#include <vector>

#include "Session.h"

class ArgParser
{
public:
	ArgParser(const std::vector<std::string> &args);

	std::string get_source_path() const;
	std::string get_destination_path() const;
	bool is_command_parsed() const;

private:
	std::string local_file;
	std::string remote_file;
	bool parsing_succeed = false;

};

int main(int argc, char* argv[])
{
	bool on_debug = true;

	if (argc > 1)
		on_debug = false;

	std::vector<std::string> arg_values;

	for (int i = 1; i < argc; ++i)
	{
		arg_values.emplace_back(std::string(argv[i]));
	}

	ArgParser args(arg_values);

	if (!args.is_command_parsed() and !on_debug)
		return 0;
	

	std::string host = "127.0.0.1";
	int port = 8887;
	std::string login = "not used";
	std::string passw = "root";
	
	int file_access_type = O_WRONLY | O_CREAT | O_TRUNC; 
	int file_permissions = 0700; //S_IRWXU = 0700 on linux, std::filesystem::perms::owner_all for C++17
	
	std::string source_file = "./test_file.dat";

	int folder_permissions = file_permissions;
	std::string dest_file = "f1/f2/test_dest.dat";

	if (!on_debug)
	{
		std::string source_file = args.get_source_path();
		std::string dest_file = args.get_destination_path();
	}
	std::string dest_dir = dest_file.substr(0, dest_file.find_last_of("/\\"));

	Session session;

	try
	{
		session.Connect(host, port)
			.Login(login, passw)
			//.CreateDir(dest_dir, folder_permissions)
			.SendFile(source_file, dest_file, file_access_type, file_permissions);
	}
	catch (std::exception &ex)
	{
		std::cout << "[error] " << ex.what() << std::endl;
	}

	std::cout << "Press Enter to exit." << std::endl;
	std::cin.get();
}


ArgParser::ArgParser(const std::vector<std::string> & args)
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


}

std::string ArgParser::get_source_path() const
{
	return local_file;
}
std::string ArgParser::get_destination_path() const
{
	return remote_file;
}
bool ArgParser::is_command_parsed() const
{
	return parsing_succeed;
}
