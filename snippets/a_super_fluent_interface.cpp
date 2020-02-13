#include <iostream>
#include <memory>

class NonAuthUser;

class AuthUser
{
public:
    virtual std::shared_ptr<NonAuthUser> LogOut() = 0;
};

class NonAuthUser
{
public:
    virtual std::shared_ptr<AuthUser> Login() = 0;
};


class Session: public NonAuthUser, public AuthUser, public std::enable_shared_from_this<Session>
{
public:
    Session()
    {
        std::cout << "Session()" << std::endl;
    }

    std::shared_ptr<NonAuthUser> Init()
    {
        std::cout << "Init()" << std::endl;

        return shared_from_this();
    }

    virtual std::shared_ptr<AuthUser> Login() override
    {
        std::cout << "Login()" << std::endl;

        return shared_from_this();
    }

    virtual std::shared_ptr<NonAuthUser> LogOut() override
    {
        std::cout << "LogOut()" << std::endl;

        return shared_from_this();
    }
};

std::shared_ptr<NonAuthUser> InitSession()
{
    return std::make_shared<Session>()->Init();
}

int main()
{
    InitSession()->Login()->LogOut();
}
