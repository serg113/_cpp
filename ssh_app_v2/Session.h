/*
 this module depends on "libssh" library 
 
 to use ssh session API:  
 1. include "Session.h" header file		
	#include "Session.h"
		
 2.1 create session object and make chained calls to available functions
	Ssh().Connect(host, port)
			.Login(login, passw)
				.CreateDir(dir, perms)
					.SendFile(source, dest, access_type, perms);

 2.2 initialize session object, connect to remote host, then use file transfer functions where you need
	Ssh ssh;
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


#ifndef SA_SESSION_H
#define SA_SESSION_H

class InitializedSession
{
public:
	virtual InitializedSession& CreateDir(const std::string &dir, int permissions) = 0;

	virtual InitializedSession& SendFile(const std::string &source,
											const std::string &destination,
												int access_type,
													int permissions,
														bool create_dir = false
															) = 0;
};

class NotInitializedSession
{
public:
	virtual InitializedSession& Login(const std::string &login, const std::string &password) = 0;
};


class Session : NotInitializedSession, InitializedSession
{
public:
	friend class Ssh;

	virtual InitializedSession& Login(const std::string &login, const std::string &password) override;
	virtual InitializedSession& CreateDir(const std::string &dir, int permissions) override;
	virtual InitializedSession& SendFile (const std::string &source,
											const std::string &destination,
												int access_type,
													int permissions,
														bool create_dir = false
															) override;

	~Session();

private:
	Session();
	Session(const Session& sess) = default;
	Session& operator=(const Session& sess) = default;
	
	ssh_session session_;
	sftp_session sftp_;

	void InitSftp();
	NotInitializedSession& Connect(const std::string &host, int port);
};

class Ssh
{
public:
	Ssh();
	~Ssh();
	NotInitializedSession& Connect(const std::string &host, int port);

private:
	Session* session_;
};


#endif // SA_SESSION_H
