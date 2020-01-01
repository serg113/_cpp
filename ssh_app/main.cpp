//#include <sys/stat.h>
#include <fcntl.h>
#include <vector>

#include "ArgParser.h"
#include "Session.h"



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

	if (!args.is_command_parsed() && !on_debug)
		return 0;
	

	std::string host = "127.0.0.1";
	int port = 8887;
	std::string login = "not used";
	std::string passw = "root";
	
	int file_access_type = O_WRONLY | O_CREAT | O_TRUNC; 
	int file_permissions = 0700; //S_IRWXU = 0700 on linux, std::filesystem::perms::owner_all for C++17
	int folder_permissions = file_permissions;
	
	std::string source_file;
	std::string dest_file;

	if (on_debug)
	{
		source_file = "./test_file.dat";
		dest_file = "f1/f2/test_dest.dat";
	}
	else
	{
		source_file = args.get_source_path();
		dest_file = args.get_destination_path();
	}
	std::string dest_dir = dest_file.substr(0, dest_file.find_last_of("/\\"));

	std::cout << source_file << " : " << dest_file << std::endl;

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


