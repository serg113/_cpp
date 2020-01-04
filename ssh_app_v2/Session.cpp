#include "Session.h"


Ssh::Ssh()
{
	session_ = new Session();
}

Ssh::~Ssh()
{
	delete session_;
}

NotInitializedSession& Ssh::Connect(const std::string &host, int port)
{
	return session_->Connect(host, port);
}

Session::Session()
{
	session_ = NULL;
	sftp_ = NULL;
	logger_.log(">>> session created");
}

Session::~Session()
{
	if (sftp_ != NULL)
	{
		sftp_free(sftp_);
	}

	if (session_ != NULL)
	{
		ssh_disconnect(session_);
		ssh_free(session_);
	}
	logger_.log("<<< session destructed");
}

NotInitializedSession& Session::LogOut() 
{	
	sftp_free(sftp_);
	sftp_ = NULL;
	
	ssh_disconnect(session_);

	Connect(remote_host_, port_);

	logger_.log(">> logged out");

	return *this;
};

NotInitializedSession& Session::Connect(const std::string &host, int port)
{
	remote_host_ = host;
	port_ = port;

	session_ = ssh_new();

	if (session_ == NULL)
		throw std::exception("ssh session has not been initialized");

	ssh_options_set(session_, SSH_OPTIONS_HOST, host.c_str());
	ssh_options_set(session_, SSH_OPTIONS_PORT, &port);
	//ssh_options_set(session_, SSH_OPTIONS_LOG_VERBOSITY, &verb);
	//ssh_options_set(ssh_session_, SSH_OPTIONS_USER, "user");

	if (ssh_connect(session_) == SSH_OK)
	{
		logger_.log("[ok] successfully connected");
	}
	else
	{
		throw std::exception("cannot connect to remote host");
	}

	return *this;
}

InitializedSession& Session::Login(const std::string &login, const std::string &password)
{
	if (ssh_userauth_password(session_, login.c_str(), password.c_str()) == SSH_AUTH_SUCCESS)
	{
		logger_.log("[ok] successfully authorized");
	}
	else
	{
		throw std::exception("cannot authorize session");
	}

	return *this;
}

InitializedSession& Session::CreateDir(const std::string &dir, int permissions)
{
	InitSftp();

	//std::replace(remote_file.begin(), remote_file.end(), '\\', '/');

	std::size_t first_pos = 0, second_pos;

	while (true)
	{
		second_pos = dir.find("/", first_pos);

		if (second_pos != std::string::npos || dir.substr(first_pos).size() > 0)
		{
			int rsp = sftp_mkdir(sftp_, dir.substr(0, second_pos).c_str(), permissions);

			if (rsp != SSH_OK)
			{
				if (sftp_get_error(sftp_) != SSH_FX_FILE_ALREADY_EXISTS)
					logger_.log("[info] directory already exists: " + dir.substr(0, second_pos));
			}
			else
			{
				logger_.log("[ok] folder created : " + dir.substr(0, second_pos));
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

InitializedSession& Session::SendFile(const std::string &source, const std::string &destination, int access_type, int permissions, bool create_dir)
{
	InitSftp();

	if (create_dir && destination.find_last_of("/\\") != std::string::npos)
		this->CreateDir(destination.substr(0, destination.find_last_of("/\\")), permissions);

	sftp_file remote_file = sftp_open(sftp_, destination.c_str(), access_type, permissions);

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
		}

		logger_.log(
			"data successfully written, last part of file: " + 
			std::string(buffer.begin(), buffer.begin() + local_file.gcount())
		);
	}

	local_file.close();
	sftp_close(remote_file);

	return *this;
}

void Session::InitSftp()
{
	if (sftp_ != NULL)
		return;

	sftp_ = sftp_new(session_);

	if (sftp_ == NULL)
		throw std::exception("cannot allocate sftp session");

	if (sftp_init(sftp_) != SSH_OK)
		throw std::exception("cannot initialize sftp session");
}
