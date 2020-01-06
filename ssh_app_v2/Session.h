/*
 this module depends on "libssh" library 
 
 to use ssh session API:  
 1. include "Session.h" header file		
	#include "Session.h"
		
 2.1 create session object and make chained calls to available functions
	SshConnector().Connect(host, port)
			.Login(login, passw)
				.CreateDir(dir, perms)
					.SendFile(source, dest, access_type, perms);

 2.2 initialize session object, connect to remote host, then use file transfer functions where you need
	SshConnector ssh;
	auto& session = ssh.Connect(host, port).Login(login, passw);
	...
	for (auto& dir : dirs)
	{
		session.CreateDir(dir, perms);
	}
	...
		

 */


#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <algorithm>
#include <memory>

#include "ssh_library\libssh\libssh.h"
#include "ssh_library\libssh\sftp.h"

#include "SessionBase.h"
#include "Logger.h"

#ifndef SA_SESSION_H
#define SA_SESSION_H

class Session : NotInitializedSession, InitializedSession
{
public:
	friend class SshConnector;

	virtual InitializedSession& Login(const std::string &login, const std::string &password) override;
	virtual InitializedSession& CreateDir(const std::string &dir, int permissions) override;
	virtual InitializedSession& SendFile(const std::string &source,
		const std::string &destination,
		int access_type,
		int permissions,
		bool create_dir = false
	) override;
	virtual NotInitializedSession& LogOut() override;

	~Session();

private:
	Session() = default;
	Session(std::shared_ptr<Logger> logger);
	Session(const Session& sess) = default;
	Session& operator=(const Session& sess) = default;

	NotInitializedSession& Connect(const std::string &host, int port);
	void InitSftp();
	void ReleaseSftp();
	void ReleaseSsh();
	
	ssh_session ssh_session_;
	sftp_session sftp_;
	std::string remote_host_;
	int port_;
	std::shared_ptr<Logger> logger_;
};


class SshConnector
{
public:
	SshConnector();
	~SshConnector();
	SshConnector& SetLogger(std::shared_ptr<Logger> logger);
	NotInitializedSession& Connect(const std::string &host, int port);

private:
	Session* session_; 
	std::shared_ptr<Logger> logger_;
};

#endif // SA_SESSION_H
