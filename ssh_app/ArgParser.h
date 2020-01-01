#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#ifndef SA_ARGPARSER_H
#define SA_ARGPARSER_H

class ArgParser
{
public:
	ArgParser();
	bool ProcessArgs(const std::vector<std::string> &args);

	std::string get_source_path() const;
	std::string get_destination_path() const;

private:
	std::string local_file;
	std::string remote_file;
	bool parsing_succeed = false;

};

#endif // SA_ARGPARSER_H
