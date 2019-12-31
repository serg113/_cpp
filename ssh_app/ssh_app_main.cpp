#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include "ssh_library/libssh/libssh.h"
#include "ssh_library/libssh/sftp.h"

#include <sys/stat.h>
#include <fcntl.h>

class Session
{
private:
	ssh_session session;
	sftp_session sftp;

public:
	Session() {};

	~Session()
	{
		if (sftp != NULL)
		{
			sftp_free(sftp);
		}
			
		if (session != NULL)
		{
			ssh_disconnect(session);
			ssh_free(session);
		}
	}

	Session& Connect(const std::string &host, int port)
	{
		session = ssh_new();

		if (session == NULL)
			throw std::exception("ssh session has not been initialized");
		
		ssh_options_set(session, SSH_OPTIONS_HOST, host.c_str());
		ssh_options_set(session, SSH_OPTIONS_PORT, &port);
		//ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, &verb);
		//ssh_options_set(ssh_session_, SSH_OPTIONS_USER, "user");

		if (ssh_connect(session) == SSH_OK)
		{
			std::cout << "[ok] successfully connected" << std::endl;
		}
		else
		{
			throw std::exception("cannot connect to remote host");
		}

		return *this;
	}

	Session& Login(const std::string &login, const std::string &password)
	{
		if (ssh_userauth_password(session, NULL, password.c_str()) == SSH_AUTH_SUCCESS)
		{
			std::cout << "[ok] successfully authorized" << std::endl;
		}
		else
		{
			throw std::exception("cannot authorize session");
		}

		return *this;
	}

	Session& CreateDir(const std::string &dir, int permissions)
	{
		InitSftp();

		std::size_t first_pos = 0, second_pos;

		while (true)
		{
			second_pos = dir.find("/", first_pos);

			if (second_pos != std::string::npos || dir.substr(first_pos).size() > 0)
			{
				int rc = sftp_mkdir(sftp, dir.substr(0, second_pos).c_str(), permissions);

				if (rc != SSH_OK)
				{
					if (sftp_get_error(sftp) != SSH_FX_FILE_ALREADY_EXISTS)
						std::cout << "[info] directory already exists: " 
									<< dir.substr(0, second_pos) << std::endl;
				}
				else
				{
					std::cout << "[ok] folder created : " << dir.substr(0, second_pos) << std::endl;
				}
				first_pos = second_pos + 1;

				if (second_pos == std::string::npos)
					break;
			}
			else
			{
				break;
			}
		}

		return *this;
	}

	Session& SendFile(const std::string &source, const std::string &destination, int access_type, int permissions)
	{
		InitSftp();

		sftp_file remote_file = sftp_open(sftp, destination.c_str(), access_type, permissions);

		if (remote_file == NULL)
			throw std::exception("cannot open remote file");

		std::ifstream local_file;

		local_file.open(source.c_str(), std::ios::binary);

		if (local_file.is_open())
		{
			std::string chunk;

			while (std::getline(local_file, chunk))
			{
				std::cout << chunk << std::endl;

				std::size_t written_bytes = sftp_write(remote_file, chunk.c_str(), chunk.size());

				if (written_bytes != chunk.size())
					throw std::exception("cannot write to remote file");
			}
		}
		sftp_close(remote_file);

		return *this;
	}

private:

	void InitSftp()
	{
		if (sftp != NULL) 
			return;

		sftp = sftp_new(session);

		if (sftp == NULL)
			throw std::exception("cannot allocate sftp session");

		if (sftp_init(sftp) != SSH_OK)
			throw std::exception("cannot initialize sftp session");
	}
};

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
