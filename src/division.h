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

        // Perform long division
        BigNumber quotient;
        BigNumber remainder = dividend;
        while (remainder.digits.size() >= divisor.digits.size())
        {
            int digit = 0;
            while (!std::lexicographical_compare(divisor.digits.rbegin(), divisor.digits.rend(), remainder.digits.rbegin(), remainder.digits.rend()))
            {
                // Subtract the divisor from the remainder
                std::vector<int> difference;
                int borrow = 0;
                for (int i = 0; i < remainder.digits.size(); i++)
                {
                    const int a = i < remainder.digits.size() ? remainder.digits[i] : 0;
                    const int b = i < divisor.digits.size() ? divisor.digits[i] : 0;
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
                remainder = std::move(difference);
                digit++;
            }
            quotient.digits.push_back(digit);
            remainder.digits.resize(remainder.digits.size() - divisor.digits.size());
        }
        // Remove leading zeros
        quotient.digits.erase(std::find_if(quotient.digits.rbegin(), quotient.digits.rend(), [](int digit) { return digit != 0; }).base(), quotient.digits.end());
        return quotient;
        

        // Perform long division
        //BigNumber quotient;
        //BigNumber remainder = dividend;
        //while (remainder.digits.size() >= divisor.digits.size() && !(remainder.digits.size() == 1 && remainder.digits[0] == 0))
        //{
        //    int digit = 0;
        //    while (std::lexicographical_compare(divisor.digits.rbegin(), divisor.digits.rend(), remainder.digits.rbegin(), remainder.digits.rend()))
        //    {
        //        // Subtract the divisor from the remainder
        //        std::vector<int> difference;
        //        int borrow = 0;
        //        for (int i = 0; i < remainder.digits.size(); i++)
        //        {
        //            const int a = i < remainder.digits.size() ? remainder.digits[i] : 0;
        //            const int b = i < divisor.digits.size() ? divisor.digits[i] : 0;
        //            int diff = a - b - borrow;
        //            if (diff < 0)
        //            {
        //                borrow = 1;
        //                diff += 10;
        //            }
        //            else
        //            {
        //                borrow = 0;
        //            }
        //            difference.push_back(diff);
        //        }
        //        // Remove leading zeros
        //        difference.erase(std::find_if(difference.rbegin(), difference.rend(), [](int digit) { return digit != 0; }).base(), difference.end());
        //        remainder = std::move(difference);
        //        digit++;
        //    }
        //    quotient.digits.push_back(digit);
        //    remainder.digits.resize(remainder.digits.size() - divisor.digits.size());
        //}
        //// Remove leading zeros
        //quotient.digits.erase(std::find_if(quotient.digits.rbegin(), quotient.digits.rend(), [](int digit) { return digit != 0; }).base(), quotient.digits.end());
        //return quotient;
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