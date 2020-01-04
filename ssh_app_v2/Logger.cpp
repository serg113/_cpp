#include "Logger.h"

void Logger::log(const std::string& msg)
{
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string date(std::ctime(&time));

	std::cout << date.substr(0, date.size() - 6) << ": " << msg << std::endl;
}
