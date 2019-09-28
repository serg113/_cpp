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
        return error_message.c_str();
    }
};

enum class LogLevel {info = 1, error = 2, warning = 4};

std::ostream& operator<<(std::ostream& stream, LogLevel lv)
{
    switch(lv)
    {
        case LogLevel::info: stream << "info";  break;
        case LogLevel::error: stream << "error"; break;
        case LogLevel::warning: stream << "warning"; break;
        default : stream.setstate(std::ios_base::failbit);
    }
    return stream;
}

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
        if(log_file.is_open())
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
                        std::cout << "[" << LogLevel::info << "] Logger(), opened file: " << file_path << std::endl;
                }
                catch(const std::exception& ex)
                {
                    if(verbose_)
                        std::cout << "[" << LogLevel::error << "] Logger(), provided path: "
                                    << file_path << ", " << ex.what() << std::endl;

                    throw LogError(ex.what());
                }
                break;

            case LogWritingMode::append:
                throw LogError("not implemented"); break;
        }
    }

    info(const std::string& message) noexcept
    {
        try
        {
            write_log_message(LogLevel::info, message);
        }
        catch(const std::exception& err)
        {
            std::cerr << err.what() << std::endl;
        }
    }

    error(const std::string& message) noexcept
    {
        try
        {
            write_log_message(LogLevel::error, message);
        }
        catch(const std::exception& err)
        {
            std::cerr << err.what() << std::endl;
        }
    }

private:
    write_log_message(const LogLevel lv, const std::string& message)
    {
        if(!log_file.is_open())
            throw LogError("*** there is no open file to write message");

        log_file << "[" << lv << "] " << message << std::endl;

        if(verbose_)
            std::cerr << "[" << lv << "] " << message << std::endl;
    }
};

int main()
{
    Logger log;

    try
    {
        log.init("hel\\lo.log", LogWritingMode::write);
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    log.info("hello");
}
