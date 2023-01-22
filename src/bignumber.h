//Daren Shamoun
#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <cstdlib>


//wrapper around the vector of ints that allows the sign of the value to be stored
struct BigNumber 
{
    std::vector<int> digits;
    bool isPositive = true;

	BigNumber() = default;
    
	//conversion from string
    BigNumber(const std::string& value)
    {
		if (value[0] == '-')
		{
			isPositive = false;
		}
		for (size_t i = value.size() - 1; i >= 0; i--)
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