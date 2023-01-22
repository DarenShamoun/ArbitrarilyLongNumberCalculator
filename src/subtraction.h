//Daren Shamoun
#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "operation.h"

#include <algorithm>
#include <vector>
#include <memory>
#include <exception>
#include <stdexcept>


//define subtraction operation
class Subtraction : public Operation
{
public:
    BigNumber handle(const std::vector<BigNumber>& operands) const override
    {
        // Make sure there are exactly two operands
        if (operands.size() != 2)
        {
            throw std::invalid_argument("Subtraction requires exactly two operands");
        }

        const BigNumber& minuend = operands[0];
        const BigNumber& subtrahend = operands[1];

        // Check if the minuend is smaller than the subtrahend
        if (minuend.digits.size() < subtrahend.digits.size() ||
            (minuend.digits.size() == subtrahend.digits.size() && std::lexicographical_compare(minuend.digits.rbegin(), minuend.digits.rend(), subtrahend.digits.rbegin(), subtrahend.digits.rend())))
        {
            // If the minuend is smaller than the subtrahend, swap the operands and negate the result
            std::vector<int> difference;
            int borrow = 0;
            for (int i = 0; i < subtrahend.digits.size(); i++)
            {
                const int a = i < minuend.digits.size() ? minuend.digits[i] : 0;
                const int b = i < subtrahend.digits.size() ? subtrahend.digits[i] : 0;
                int diff = b - a - borrow;
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
            difference.front() *= -1;
            // Remove leading zeros
            difference.erase(std::find_if(difference.rbegin(), difference.rend(), [](int digit) { return digit != 0; }).base(), difference.end());
            return difference;
        }

        // If the minuend is not smaller than the subtrahend, subtract the subtrahend from the minuend
        std::vector<int> difference;
        int borrow = 0;
        for (size_t i = 0; i < minuend.digits.size(); i++)
        {
            const int a = i < minuend.digits.size() ? minuend.digits[i] : 0;
            const int b = i < subtrahend.digits.size() ? subtrahend.digits[i] : 0;
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
        return difference;
    }

    size_t GetOperandCount() const override
    {
        return 2;
    }

    std::unique_ptr<Operation> Clone() const override
    {
        return std::make_unique<Subtraction>(*this);
    }
};

#endif // !SUBTRACTION_H
