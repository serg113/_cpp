//#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <string>

#include "ArgParser.h"
#include "Session.h"

int main(int argc, char* argv[])
{
	std::shared_ptr<Logger> logger_ = std::make_shared<Logger>();

	bool is_cmd_used = (argc > 1);

	ArgParser parser(logger_);

	if (is_cmd_used)
	{
		std::vector<std::string> arg_values;

		for (int i = 1; i < argc; ++i)
			arg_values.emplace_back(std::string(argv[i]));

		if(!parser.ProcessArgs(arg_values))
			return 0;
	}

	std::string host = "127.0.0.1";
	int port = 8887;
	std::string login = "not used";
	std::string passw = "root";
	
	int access_type = O_WRONLY | O_CREAT | O_TRUNC; 
	int file_permissions = 0700; //S_IRWXU = 0700 on linux, std::filesystem::perms::owner_all for C++17
	int perms = file_permissions;
	
	std::string source;
	std::string dest;

	if (is_cmd_used){
		source = parser.get_source_path();
		dest = parser.get_destination_path();
	} 
	else {
		source = "./test_file.dat";
		dest = "f1/f2/test_dest.dat";
	}
	std::string dir = dest.substr(0, dest.find_last_of("/\\"));
	std::vector<std::string> dirs = { dir, dir };

	try
	{
		Ssh().SetLogger(logger_)
			.Connect(host, port)
			.Login("sergey2", "root2")
			.CreateDir(dir, perms)
			.LogOut()
			.Login("sergey3", "root3")
			.SendFile(source, dest, access_type, perms);

		// api usage sample 1
		//Ssh().Connect(host, port)
		//		.Login(login, passw)
		//			.CreateDir(dir, perms)
		//				.SendFile(source, dest, access_type, perms);

		//// api usage sample 2
		//Ssh ssh;
		//auto& session = ssh.Connect(host, port)
		//	.Login(login, passw);
		//
		//for (auto& dir : dirs)
		//{
		//	session.CreateDir(dir, perms);
		//}
		
	}
	catch (std::exception &ex)
	{
		logger_->error(ex.what());
	}

	std::cout << "Press Enter to exit." << std::endl;
	std::cin.get();
}


