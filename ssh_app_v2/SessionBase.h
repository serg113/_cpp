#include <string>
#include <memory>

#ifndef SA_SESSIONBASE_H
#define SA_SESSIONBASE_H

class AuthorizedSession;
class NotAuthorizedSession;
class NotConnectedSession;

using InitedSess_ = std::shared_ptr<AuthorizedSession>;
using UnInitedSess_ = std::shared_ptr<NotAuthorizedSession>;
using UnConnectedSess_ = std::shared_ptr<NotConnectedSession>;

class AuthorizedSession
{
public:
	virtual InitedSess_ CreateDir(const std::string &dir, int permissions) = 0;

	virtual InitedSess_ SendFile(const std::string &source,
					const std::string &destination,
						int access_type,
							int permissions,
								bool create_dir = false
									) = 0;
	virtual UnInitedSess_ LogOut() = 0;
};

class NotAuthorizedSession
{
public:
	virtual InitedSess_ Login(const std::string &login, const std::string &password) = 0;
};

class NotConnectedSession
{
public:
	virtual UnInitedSess_ Connect(const std::string &host, int port) = 0;
};

#endif // SA_SESSIONBASE_H
