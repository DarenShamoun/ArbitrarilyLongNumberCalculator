//Daren Shamoun
#ifndef DIVISION_H
#define DIVISION_H

#include "operation.h"

#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>


//define division operation
class Division : public Operation
{
public:
    BigNumber handle(const std::vector<BigNumber>& operands) const override
    {
        // Make sure there are exactly two operands
        if (operands.size() != 2)
        {
            throw std::invalid_argument("Division requires exactly two operands");
        }

        const BigNumber& dividend = operands[0];
        const BigNumber& divisor = operands[1];

        // Check for division by zero
        if (std::all_of(divisor.digits.begin(), divisor.digits.end(), [](int digit) { return digit == 0; }))
        {
            throw std::invalid_argument("Division by zero is not allowed");
        }

        // Check if one of the numbers is negative
        bool isNegative = false;
        if (dividend.isPositive != divisor.isPositive)
        {
            isNegative = true;
        }

        BigNumber quotient;
        quotient.isPositive = !isNegative;

        // Check if the dividend is smaller than the divisor
        if (dividend < divisor)
        {
            quotient.digits = { 0 };
            return quotient;
        }

        // Perform long division
        std::vector<int> currentDigits;
        for (int i = 0; i < dividend.digits.size(); i++)
        {
            currentDigits.push_back(dividend.digits[i]);

            int digit = 0;
            while (currentDigits.size() >= divisor.digits.size() && !(divisor < currentDigits))
            {
                std::vector<int> difference;
                int borrow = 0;
                for (int j = 0; j < currentDigits.size(); j++)
                {
                    int a = j < currentDigits.size() ? currentDigits[j] : 0;
                    int b = j < divisor.digits.size() ? divisor.digits[j] : 0;
                    int diff = a - b - borrow;
                    if (diff < 0)
                    {
                        borrow = 1;
                        diff += 10;
                    }
                    else
                    {
                        borrow = 0;
                    }
                    difference.push_back(diff);
                }
                // Remove leading zeros
                difference.erase(std::find_if(difference.rbegin(), difference.rend(), [](int digit) { return digit != 0; }).base(), difference.end());
                currentDigits = difference;
                digit++;
            }
            quotient.digits.push_back(digit);

            // Add the next digit to currentDigits if there is one
            if (i + 1 < dividend.digits.size())
            {
                currentDigits.insert(currentDigits.begin(), dividend.digits[i + 1]);
            }
        }

        // Remove leading zeros
        quotient.digits.erase(std::find_if(quotient.digits.rbegin(), quotient.digits.rend(), [](int digit) { return digit != 0; }).base(), quotient.digits.end());
        return quotient;
    }

    size_t GetOperandCount() const override
    {
        return 2;
    }

    std::unique_ptr<Operation> Clone() const override
    {
        return std::make_unique<Division>(*this);
    }
};

#endif // !DIVISION_H