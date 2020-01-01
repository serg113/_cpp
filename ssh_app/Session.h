#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <algorithm>

#include "ssh_library\libssh\libssh.h"
#include "ssh_library\libssh\sftp.h"


#ifndef SA_SESSION_H
#define SA_SESSION_H

class Session
{

public:
	static Session Create();

	~Session();

	Session& Connect(const std::string &host, int port);

	Session& Login(const std::string &login, const std::string &password);

	Session& CreateDir(const std::string &dir, int permissions);

	Session& SendFile(const std::string &source,
						const std::string &destination, 
							int access_type, 
								int permissions,
									bool create_dir = false);

private:
	Session();
	Session& operator=(const Session& sess) = default;
	Session(const Session& sess) = default;
	

	ssh_session session;
	sftp_session sftp;

	void InitSftp();
};



#endif //SA_SESSION_H
