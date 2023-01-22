//Daren Shamoun
//ID# 5550016094
#include "options.h"

namespace mesa
{
	//displays the possible command line arguements
	std::string usage(const char* argv)
	{
		const std::string input(argv);
		std::string usage = "Usage: " + input + " [-h] [-v] [expression]\n";

		return usage;
	}

	//displays the full help text along with the file name
	std::string help(const char* argv)
	{
		std::string helpText = usage(argv) +
			"\n-h:	Displays the help text and exits." +
			"\n-v:	Produce verbose output\n" +
			"\n<: The name of the file to read from. " +
			"\nIf no file name is provided, the program will run interactively." +
			"\n to quit at anytime enter 'quit'\n";

		return helpText;
	}

	//parses the command line arguements and returns the users desired settings
	mesa::option get_options(int argc, char** argv)
	{
		mesa::option userOptions{};

		//loops through each arguement
		for (auto i = 0; i < argc; i++)
		{
			//if found displays help text
			if (std::strcmp(argv[i], "-h") == 0)
			{
				std::cout << help(argv[i]) << '\n';
				exit(0);
			}

			//if found displays verbose output
			if (std::strcmp(argv[i], "-v") == 0)
			{
				userOptions.verbose = true;
			}

			//if found sets the file name
			if (std::strcmp(argv[i], "<") == 0)
			{
				if (i + 1 >= argc)
				{
					// display an error message if no filename was specified
					std::cout << "Invalid entry! (<)\n";
					std::cout << "No filename specified after '<' !\n";
					exit(0);
				}

				// store the filename specified after the < option
				userOptions.filename = argv[i + 1];
				userOptions.load = true;
			}
		}
		return userOptions;
	}
}