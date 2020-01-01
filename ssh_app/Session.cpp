#include "Session.h"


Session::Session()
{
	session = NULL;
	sftp = NULL;
};

Session::~Session()
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


Session& Session::Connect(const std::string &host, int port)
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

Session& Session::Login(const std::string &login, const std::string &password)
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

Session& Session::CreateDir(const std::string &dir, int permissions)
{
	InitSftp();

	//std::replace(remote_file.begin(), remote_file.end(), '\\', '/');

	std::size_t first_pos = 0, second_pos;

	while (true)
	{
		second_pos = dir.find("/", first_pos);

		if (second_pos != std::string::npos || dir.substr(first_pos).size() > 0)
		{
			int rsp = sftp_mkdir(sftp, dir.substr(0, second_pos).c_str(), permissions);

			if (rsp != SSH_OK)
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

Session& Session::SendFile(const std::string &source, const std::string &destination, int access_type, int permissions, bool create_dir)
{
	InitSftp();

	if (create_dir && destination.find_last_of("/\\") != std::string::npos)
		this->CreateDir(destination.substr(0, destination.find_last_of("/\\")), permissions);

	sftp_file remote_file = sftp_open(sftp, destination.c_str(), access_type, permissions);

	if (remote_file == NULL)
		throw std::exception("cannot open remote file");

	std::ifstream local_file;

	local_file.open(source.c_str(), std::ios::binary);

	if (local_file.is_open())
	{
		std::vector<char> buffer(24, 0); // need to set to max size

		while (!local_file.eof()) {

			local_file.read(buffer.data(), buffer.size());

			std::size_t written_bytes = sftp_write(remote_file, buffer.data(), local_file.gcount());

			if (written_bytes != local_file.gcount())
				throw std::exception("cannot write to remote file");

			for (int i = 0; i < local_file.gcount(); ++i) { std::cout << buffer[i]; } std::cout << std::endl;
		}

		/*std::string chunk;

		while (std::getline(local_file, chunk))
		{
			std::cout << chunk << std::endl;

			std::size_t written_bytes = sftp_write(remote_file, chunk.c_str(), chunk.size());

			if (written_bytes != chunk.size())
				throw std::exception("cannot write to remote file");
		}*/
	}

	local_file.close();
	sftp_close(remote_file);

	return *this;
}

void Session::InitSftp()
{
	if (sftp != NULL)
		return;

	sftp = sftp_new(session);

	if (sftp == NULL)
		throw std::exception("cannot allocate sftp session");

	if (sftp_init(sftp) != SSH_OK)
		throw std::exception("cannot initialize sftp session");
}
