#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#pragma warning(disable : 4996)

#ifndef SA_LOGGER_H
#define SA_LOGGER_H

class Logger
{
public:
	void log(const std::string& msg) const;
	void info(const std::string& msg) const;
	void error(const std::string& msg) const;
	void cmd(const std::string& msg) const;
};

#endif //SA_LOGGER_H