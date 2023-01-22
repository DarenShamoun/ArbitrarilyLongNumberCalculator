//Daren Shamoun
//ID# 5550016094
#ifndef CISC187_MESA_OPTIONS_H
#define CISC187_MESA_OPTIONS_H

#include <string>
#include <iostream>
#include <algorithm>


namespace mesa
{
	struct option
	{
		bool valid = true;
		bool load = false;
		bool again = true;
		bool verbose = false;
		std::string filename = "input.txt";
	};

	//displays the possible command line arguements
	std::string usage(const char* argv);
	
	//displays the full help text along with the file name
	std::string help(const char* argv);

	//parses the command line arguements and returns the users desired settings
	mesa::option get_options(int argc, char** argv);
}
#endif // !CISC187_MESA_OPTIONS_H