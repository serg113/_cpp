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
	void log(const std::string& msg);
};

#endif //SA_LOGGER_H