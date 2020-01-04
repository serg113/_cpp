#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "Logger.h"

#ifndef SA_ARGPARSER_H
#define SA_ARGPARSER_H

class ArgParser
{
public:
	ArgParser(std::shared_ptr<Logger> logger);
	bool ProcessArgs(const std::vector<std::string> &args);

	std::string get_source_path() const;
	std::string get_destination_path() const;

private:
	std::string local_file_;
	std::string remote_file_;

	void PrintHelp() const;
	void PrintHelpHint() const;

	std::shared_ptr<Logger> logger_;
};

#endif // SA_ARGPARSER_H
