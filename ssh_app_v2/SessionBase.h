#include <string>

#ifndef SA_SESSIONBASE_H
#define SA_SESSIONBASE_H

class NotInitializedSession;

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
	virtual NotInitializedSession& LogOut() = 0;
};

class NotInitializedSession
{
public:
	virtual InitializedSession& Login(const std::string &login, const std::string &password) = 0;
};

#endif // SA_SESSIONBASE_H
