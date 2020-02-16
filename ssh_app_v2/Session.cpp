#include "Session.h"

// friend of Session
UnConnectedSess_ CreateSession(std::shared_ptr<Logger> logger)
{
	std::shared_ptr<Session> sess(new Session(logger));
	return sess;
}

// Session
Session::Session() : ssh_session_{ nullptr }, sftp_{ nullptr } { };

Session::Session(std::shared_ptr<Logger> logger) : 
	logger_{ logger }, ssh_session_{ nullptr }, sftp_{ nullptr }
{ 
	logger_->info(">>> session constructed");
};

Session::~Session()
{
	ReleaseSftp();
	ReleaseSsh();
	logger_->info(">>> session destructed");
}

UnInitedSess_ Session::LogOut()
{	
	ReleaseSftp();
	
	ssh_disconnect(ssh_session_);

	Connect(remote_host_, port_);

	logger_->info(">> logged out and reconnected to :" 
		+ remote_host_ + ":" + std::to_string(port_));

	return shared_from_this();
};

UnInitedSess_ Session::Connect(const std::string &host, int port)
{
	remote_host_ = host;
	port_ = port;

	ssh_session_ = ssh_new();

	if (ssh_session_ == nullptr) {
		throw std::exception("ssh session has not been initialized");
	}

	ssh_options_set(ssh_session_, SSH_OPTIONS_HOST, host.c_str());
	ssh_options_set(ssh_session_, SSH_OPTIONS_PORT, &port);
	//ssh_options_set(session_, SSH_OPTIONS_LOG_VERBOSITY, &verb);
	//ssh_options_set(ssh_session_, SSH_OPTIONS_USER, "user");

	if (ssh_connect(ssh_session_) != SSH_OK) {
		throw std::exception("cannot connect to remote host");	
	}
	
	logger_->info("successfully connected");

	return shared_from_this();
}

InitedSess_ Session::Login(const std::string &login, const std::string &password)
{
	if (ssh_userauth_password(ssh_session_, login.c_str(), password.c_str()) != SSH_AUTH_SUCCESS) {
		throw std::exception("cannot authorize session");
	}
	
	logger_->info("successfully authorized");

	return shared_from_this();
}

InitedSess_ Session::CreateDir(const std::string &dir, int permissions)
{
	//std::replace(remote_file.begin(), remote_file.end(), '\\', '/');
	InitSftp();
	
	std::size_t first_pos = 0, second_pos = 0;

	while (second_pos != std::string::npos && first_pos != dir.size())
	{
		second_pos = dir.find("/", first_pos);

		int rsp = sftp_mkdir(sftp_, dir.substr(0, second_pos).c_str(), permissions);

		if (rsp != SSH_OK) {
			if (sftp_get_error(sftp_) != SSH_FX_FILE_ALREADY_EXISTS)
				logger_->info("directory already exists: " + dir.substr(0, second_pos));
		}
		else {
			logger_->info("folder created : " + dir.substr(0, second_pos));
		}

		first_pos = second_pos + 1;
	}

	return shared_from_this();
}

InitedSess_ Session::SendFile(const std::string &source, const std::string &destination, int access_type, int permissions, bool create_dir)
{
	InitSftp();

	if (create_dir && destination.find_last_of("/\\") != std::string::npos) {
		this->CreateDir(destination.substr(0, destination.find_last_of("/\\")), permissions);
	}

	sftp_file remote_file = sftp_open(sftp_, destination.c_str(), access_type, permissions);

	if (remote_file == NULL) {
		throw std::exception("cannot open remote file");
	}
		
	std::ifstream local_file;

	local_file.open(source.c_str(), std::ios::binary);

	if (local_file.is_open())
	{
		std::vector<char> buffer(24, 0); // need to set to max size

		while (!local_file.eof()) 
		{
			local_file.read(buffer.data(), buffer.size());

			std::size_t written_bytes = sftp_write(remote_file, buffer.data(), local_file.gcount());

			if (written_bytes != local_file.gcount()) {
				throw std::exception("cannot write to remote file");
			}	
		}

		logger_->info(
			"data successfully written, last part of file: " + 
			std::string(buffer.begin(), buffer.begin() + local_file.gcount())
		);
	}

	local_file.close();
	sftp_close(remote_file);

	return shared_from_this();
}

void Session::InitSftp()
{
	if (sftp_ != nullptr)
		return;

	sftp_ = sftp_new(ssh_session_);

	if (sftp_ == nullptr)
		throw std::exception("cannot allocate sftp session");

	if (sftp_init(sftp_) != SSH_OK)
		throw std::exception("cannot initialize sftp session");
}

void Session::ReleaseSftp()
{
	if (sftp_ != nullptr)
	{
		sftp_free(sftp_);
		sftp_ = nullptr;
	}
}

void Session::ReleaseSsh()
{
	if (ssh_session_ != nullptr)
	{
		ssh_disconnect(ssh_session_);
		ssh_free(ssh_session_);
		ssh_session_ = nullptr;
	}
}

// end Session
