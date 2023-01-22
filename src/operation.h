//Daren Shamoun
#ifndef OPERATION_H
#define OPERATION_H

#include "bignumbercalculator.h"
#include "bignumber.h"

#include <vector>
#include <memory>
#include <cstdlib>


//virtual base class for operations
class Operation
{
public:
    virtual ~Operation() = default;
    virtual BigNumber handle(const std::vector<BigNumber>& operands) const = 0;
    virtual size_t GetOperandCount() const = 0;
    virtual std::unique_ptr<Operation> Clone() const = 0;
};

#endif // !OPERATION_H