//Daren Shamoun
#ifndef ADDITION_H
#define ADDITION_H

#include "operation.h"

#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cstdlib>


//define addition operation
class Addition : public Operation
{
public:
    // Override the base class's handle() function
    BigNumber handle(const std::vector<BigNumber>& operands) const override
    {
        BigNumber result;
        int carry = 0;
        size_t i = 0;
        for (; i < operands[0].digits.size(); i++)
        {
            int sum = carry;
            for (auto& operand : operands)
            {
                if (i < operand.digits.size())
                {
                    sum += operand.digits[i];
                }
            }
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry > 0)
        {
            result.digits.push_back(carry);
        }
        return result;
    }

    size_t GetOperandCount() const override
    {
        return 2;
    }

    std::unique_ptr<Operation> Clone() const override
    {
        return std::make_unique<Addition>(*this);
    }
};

#endif // !ADDITION_H