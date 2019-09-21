#include <iostream>
#include <string>
#include <fstream>
#include <exception>

class LogError: public std::exception
{
private:
    std::string error_message {"LogError"};

public:
    LogError() = default;

    LogError(const std::string&& message): error_message{std::move(message)} {}

    virtual ~ LogError(){}

    virtual const char* what() const throw()
    {
        return &error_message[0];
    }
};

enum class LogLevel {info = 1, error = 2, warning = 4, debug = 8};

enum class LogWritingMode {write = 1, append = 2};

class Logger
{
private:
    std::fstream log_file;
    bool verbose_ {true};

public:
    Logger(){};

    ~Logger()
    {
        log_file.close();
    }

    init(const std::string& file_path, LogWritingMode mode, bool verbose = true)
    {
        verbose_ = verbose;

        switch(mode)
        {
            case LogWritingMode::write:
                try
                {
                    log_file.open(file_path, std::fstream::out | std::fstream::trunc);

                    if(!log_file.is_open())
                        throw LogError("cannot open the file");

                    if(verbose_)
                        std::cout << "[info] Logger(), opened file: " << file_path << std::endl;
                }
                catch(std::exception& ex)
                {
                    if(verbose_)
                        std::cout << "[error] Logger(), provided path: " << file_path << ", " << ex.what() << std::endl;

                    throw LogError(ex.what());
                }
                break;

            case LogWritingMode::append:
                throw LogError("not implemented"); break;
        }
    }

    info(const std::string& message)
    {
        write_log_message(LogLevel::info, message);
    }

    error(const std::string& message)
    {
        write_log_message(LogLevel::error, message);
    }

private:
    write_log_message(const LogLevel lv, const std::string& message)
    {
        if(!log_file.is_open())
            throw LogError("log file is not open to write message");

        switch(lv)
        {
            case LogLevel::info:
                log_file << "[info] ";
                if(verbose_) std::cout << "[error] ";
                break;
            case LogLevel::error:
                log_file << "[error] ";
                if(verbose_) std::cout << "[error] ";
                break;
        }
        log_file << message << std::endl;

        if(verbose_)
            std::cout << message << std::endl;
    }
};

int main()
{
    Logger log;

    try
    {
        log.init("hello.log", LogWritingMode::write);
    }
    catch(std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    log.info("hello");
}
