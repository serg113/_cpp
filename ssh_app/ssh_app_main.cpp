#include "Session.h"

int main(int argc, char* argv[])
{	
	std::string host = "127.0.0.1";
	int port = 8887;
	std::string login = "not used";
	std::string passw = "root";
	
	int file_access_type = O_WRONLY | O_CREAT | O_TRUNC; 
	int file_permissions = 0700; //S_IRWXU = 0700 on linux, std::filesystem::perms::owner_all for C++17
	
	std::string source_file = "test_file.dat";

	int folder_permissions = file_permissions;
	std::string dest_dir = "f1/f2";
	std::string dest_file = "f1/f2/test_dest.dat";

	Session session;

	try
	{
		session.Connect(host, port)
			.Login(login, passw)
			.CreateDir(dest_dir, folder_permissions)
			.SendFile(source_file, dest_file, file_access_type, file_permissions);
	}
	catch (std::exception &ex)
	{
		std::cout << "[error] " << ex.what() << std::endl;
	}

	std::cout << "Press Enter to exit." << std::endl;
	std::cin.get();
}
