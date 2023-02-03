//Daren Shamoun
#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <cstdlib>
#include <iostream>


//wrapper around the vector of ints that allows the sign of the value to be stored
struct BigNumber 
{
    std::vector<int> digits;
    bool isPositive = true;

	BigNumber() = default;
    
	//conversion from string
	BigNumber(const std::string& value)
	{
		// Check if the input is empty
		if (value.empty())
		{
			std::cerr << "Error: empty input." << std::endl;
			exit(1);
		}

		// Check if the input contains non-numeric characters
		for (const auto& c : value)
		{
			if (!isdigit(c) && c != '-')
			{
				std::cerr << "Error: non-numeric character in input." << std::endl;
				exit(1);
			}
		}

		if (value[0] == '-')
		{
			isPositive = false;
		}
		for (size_t i = value.size() - 1; i >= (value[0] == '-' ? 1 : 0); i--)
		{
			if (value[i] != '-')
			{
				digits.push_back(value[i] - '0');
			}
		}
	}
    
    //conversion from int
	BigNumber(int value)
	{
		if (value < 0)
		{
			isPositive = false;
		}
		while (value > 0)
		{
			digits.push_back(value % 10);
			value /= 10;
		}
	}
    
    BigNumber(const std::vector<int>& digits):
        digits(digits)
    {}
    
    BigNumber(const std::vector<int>& digits, bool isPositive):
        digits(digits), isPositive(isPositive)
    {}
    
    BigNumber(std::vector<int>&& digits, bool isPositive):
        digits(std::move(digits)), isPositive(isPositive)
    {}
};

#endif // !BIG_NUMBER_H