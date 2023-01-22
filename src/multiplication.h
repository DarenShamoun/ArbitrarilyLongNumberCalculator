//Daren Shamoun
#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "operation.h"

#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>


//define multiplication operation
class Multiplication : public Operation
{
public:
    BigNumber handle(const std::vector<BigNumber>& operands) const override
    {
        // Make sure there are exactly two operands
        if (operands.size() != 2)
        {
            throw std::invalid_argument("Multiplication requires exactly two operands");
        }

        // Check if one of the operands is zero
        if (operands[0].digits.size() == 1 && operands[0].digits[0] == 0)
        {
            return { 0 };
        }
        if (operands[1].digits.size() == 1 && operands[1].digits[0] == 0)
        {
            return { 0 };
        }

        const BigNumber& multiplicand = operands[0];
        const BigNumber& multiplier = operands[1];

        std::vector<int> product(multiplicand.digits.size() + multiplier.digits.size(), 0);
        for (int i = 0; i < multiplicand.digits.size(); i++)
        {
            int carry = 0;
            for (int j = 0; j < multiplier.digits.size() || carry > 0; j++)
            {
                const int digit = j < multiplier.digits.size() ? multiplier.digits[j] : 0;
                const int sum = product[i + j] + multiplicand.digits[i] * digit + carry;
                product[i + j] = sum % 10;
                carry = sum / 10;
            }
        }

        // Remove leading zeros
        product.erase(std::find_if(product.rbegin(), product.rend(),
            [](int digit) { return digit != 0; }).base(), product.end());
        return product;
    }

    size_t GetOperandCount() const override
    {
        return 2;
    }

    std::unique_ptr<Operation> Clone() const override
    {
        return std::make_unique<Multiplication>(*this);
    }
};

#endif // !MULTIPLICATION_H