#include "Logger.h"

void Logger::log(const std::string& msg) const
{
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string date(std::ctime(&time));

	std::cout << date.substr(0, date.size() - 6) << ": " << msg << std::endl;
}

void Logger::error(const std::string& msg) const
{
	log("[error] " + msg);
}
void Logger::info(const std::string& msg) const
{
	log("[info] " + msg);
}

void Logger::cmd(const std::string& msg) const
{
	std::cout << msg << std::endl;
}
