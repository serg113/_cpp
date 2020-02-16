//#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <string>

#include "ArgParser.h"
#include "Session.h"

std::unique_ptr<ArgParser> get_parser(int argc, char* argv[], std::shared_ptr<Logger> logger);

int main(int argc, char* argv[])
{
	auto logger_ = std::make_shared<Logger>();

	auto parser_ = get_parser(argc, argv, logger_);
	
	std::string host = "127.0.0.1";
	int port = 8887;
	std::string login = "admin";
	std::string passw = "root";
	
	int access_type = O_WRONLY | O_CREAT | O_TRUNC; 
	int file_permissions = 0700; //S_IRWXU = 0700 on linux, std::filesystem::perms::owner_all for C++17
	int perms = file_permissions;
	
	std::string source;
	std::string dest;

	if (parser_){
		source = parser_->get_source_path();
		dest = parser_->get_destination_path();
	} 
	else {
		source = "./test_file.dat";
		dest = "f1/f2/test_dest.dat";
	}
	std::string dir = dest.substr(0, dest.find_last_of("/\\"));
	std::vector<std::string> dirs = { dir, dir };

	try
	{
		CreateSession(logger_)
			->Connect(host, port)
				->Login("admin", "root")
					->CreateDir(dir, perms) //->LogOut()->Login("user2", "pass2")
						->SendFile(source, dest, access_type, perms);
	}
	catch (std::exception &ex)
	{
		logger_->error(ex.what());
	}

	std::cout << "Press Enter to exit." << std::endl;
	std::cin.get();
}

std::unique_ptr<ArgParser> get_parser(int argc, char* argv[], std::shared_ptr<Logger> logger)
{
	auto parser = std::make_unique<ArgParser>(logger);

	std::vector<std::string> arg_values;

	for (int i = 1; i < argc; ++i)
		arg_values.emplace_back(std::string(argv[i]));

	if (!parser->ProcessArgs(arg_values))
		return nullptr;

	return parser;
}

