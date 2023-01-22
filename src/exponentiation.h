//Daren Shamoun
#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "operation.h"

#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>


//define exponentiation operation
class Exponent : public Operation
{
public:
    BigNumber handle(const std::vector<BigNumber>& operands) const override
    {
        // Make sure there is exactly one operand and the exponent is a positive integer
        if (operands.size() != 1 || !std::all_of(operands[0].digits.begin(), operands[0].digits.end(), [](int digit) { return digit >= 0; }) || operands[0].digits[0] <= 0)
        {
            throw std::invalid_argument("Exponent requires exactly one operand and a positive integer exponent");
        }

        const BigNumber& base = operands[0];
        const int exponent = operands[0].digits[0];

        // Perform exponentiation by repeated multiplication
        std::vector<int> result = { 1 };
        for (int i = 0; i < exponent; i++)
        {
            std::vector<int> product(result.size() + base.digits.size(), 0);
            for (int i = 0; i < result.size(); i++)
            {
                for (int j = 0; j < base.digits.size(); j++)
                {
                    product[i + j] += result[i] * base.digits[j];
                }
            }
            int carry = 0;
            for (int i = 0; i < product.size(); i++)
            {
                product[i] += carry;
                carry = product[i] / 10;
                product[i] %= 10;
            }
            // Remove leading zeros
            product.erase(std::find_if(product.rbegin(), product.rend(), [](int digit) { return digit != 0; }).base(), product.end());
            result = std::move(product);
        }
        return result;
    }

    size_t GetOperandCount() const override
    {
        return 1;
    }

    std::unique_ptr<Operation> Clone() const override
    {
        return std::make_unique<Exponent>(*this);
    }
};

#endif // !EXPONENTIATION_H