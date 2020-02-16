
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

class Session final: public NotConnectedSession,
			public NotAuthorizedSession, 
				public AuthorizedSession,
					public std::enable_shared_from_this<Session>
{
public:
	// prefer not friend not member functions
	friend UnConnectedSess_ CreateSession(std::shared_ptr<Logger> logger);

	virtual UnInitedSess_ Connect(const std::string &host, int port);
	virtual InitedSess_ Login(const std::string &login, const std::string &password) override;
	virtual InitedSess_ CreateDir(const std::string &dir, int permissions) override;
	virtual InitedSess_ SendFile(const std::string &source,
					const std::string &destination,
						int access_type,
							int permissions,
								bool create_dir = false
									) override;
	virtual UnInitedSess_ LogOut() override;
	
	~Session();

private:
	Session();
	Session(std::shared_ptr<Logger> logger);
	
	void InitSftp();
	void ReleaseSftp();
	void ReleaseSsh();
	
	ssh_session ssh_session_;
	sftp_session sftp_;
	std::string remote_host_;
	int port_;
	std::shared_ptr<Logger> logger_;

	bool in_test_mode{ false };
};

UnConnectedSess_ CreateSession(std::shared_ptr<Logger> logger);


#endif // SA_SESSION_H
