//Daren Shamoun
#ifndef BIG_NUMBER_CALCULATOR_H
#define BIG_NUMBER_CALCULATOR_H

#include "operation.h"
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "division.h"
#include "exponentiation.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <functional>
#include <unordered_set>
#include <memory>
#include <stdexcept>
#include <cstdlib>


//creates a operation object and registers the operations
std::unique_ptr<Operation> static CreateOperation(const std::string& token)
{
    static const std::unordered_map<std::string, std::function<std::unique_ptr<Operation>()>> factory =
    {
        { "+", []() { return std::make_unique<Addition>(); } },
        { "-", []() { return std::make_unique<Subtraction>(); } },
        { "*", []() { return std::make_unique<Multiplication>(); } },
        { "/", []() { return std::make_unique<Division>(); } },
        { "^", []() { return std::make_unique<Exponent>(); } },
    };

    auto it = factory.find(token);
    if (it == factory.end())
    {
        throw std::invalid_argument("Invalid operator");
    }
    return it->second();
}

//
bool CustomCompare(const std::vector<int>& a, const std::vector<int>& b) 
{
    if (a.size() < b.size()) return true;
    if (a.size() > b.size()) return false;

    for (int i = a.size() - 1; i >= 0; i--) 
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}

//converts a string to a vector of ints
BigNumber static ToBigNumber(const std::string& number)
{
    std::vector<int> big_number;
    for (const char& digit : number)
    {
        big_number.push_back(digit - '0');
    }
    return big_number;
}

// Helper function to create a deep copy of an `Operation` object
std::unique_ptr<Operation> static CloneOperation(const std::unique_ptr<Operation>& operation)
{
    return std::unique_ptr<Operation>(operation->Clone());
}

//the actual calculator
class BigNumberCalculator
{
private:
    //the result of the calculation
    BigNumber m_result;

	//the map of the different operations
    std::map<std::string, std::unique_ptr<Operation>> operations_;

	//checks if the token is an operator
    static bool IsOperator(const std::string& token)
    {
        static const std::unordered_set<std::string> operators = { "+", "-", "*", "/", "^" };
        return operators.count(token) > 0;
    }

	//checks the number of operands
    size_t GetOperandCount(const std::string& token)
    {
        return operations_.at(token)->GetOperandCount();
    }

	//gets the operation from the map
    std::unique_ptr<Operation>&& GetOperation(const std::string& token)
    {
        return std::move(operations_[token]);
    }

public:
    BigNumberCalculator() = default;

    //returns the result of the calculation
    BigNumber GetResult() const
    {
        return m_result;
    }

    // Register an operation with the given symbol
    void RegisterOperation(std::string symbol, std::unique_ptr<Operation> operation)
    {
        operations_[symbol] = std::move(operation);
    }

	//convert a string to a BigNumber
    BigNumber static ParseBigNumber(const std::string& number)
    {
        BigNumber bigNumber;
        for (const char ch : number)
        {
            if (!bool(isdigit(ch)))
            {
                throw std::invalid_argument("Invalid input");
            }
            bigNumber.digits.push_back(ch - '0');
        }
        std::reverse(bigNumber.digits.begin(), bigNumber.digits.end());
        return bigNumber;
    }
    
    // Calculate the result of the given expression
    void Calculate(const std::string& expression)
    {
        std::stack<BigNumber> operands;
        std::stack<std::unique_ptr<Operation>> operations;

        std::stringstream ss(expression);
        std::string token;
        while (ss >> token)
        {
            if (IsOperator(token))
            {
                auto operation = CreateOperation(token);

                // Pop the required number of operands from the operands stack
                const size_t operandCount = operation->GetOperandCount();
                std::vector<BigNumber> operationOperands;
                operationOperands.reserve(operandCount);
                for (size_t i = 0; i < operandCount; i++)
                {
                    operationOperands.push_back(operands.top());
                    operands.pop();
                }

                // Perform the operation and push the result onto the operands stack
                const BigNumber result = operation->handle(operationOperands);
                operands.push(result);

                // Push the operation onto the operations stack
                operations.push(std::move(operation));
            }
            else
            {
                // Parse the token as a big number and push it onto the operands stack
                operands.push(ParseBigNumber(token));
            }
        }

        // The result should be the only operand left on the stack
        if (operands.size() != 1)
        {
            throw std::invalid_argument("Invalid expression");
        }
        m_result = operands.top();
    }

	//checks if the token is an operand
    static bool IsOperand(const std::string& token)
    {
        return std::all_of(token.begin(), token.end(), ::isdigit);
    }

	//converts a BigNumber to a string
    std::string ToString() const
    {
        std::stringstream ss;
        std::vector<int> reversed(m_result.digits.rbegin(), m_result.digits.rend());
        for (auto digit : reversed)
        {
            ss << digit;
        }
        return ss.str();
    }

    BigNumber EvaluatePostfix(const std::vector<std::string>& postfix)
    {
        std::stack<BigNumber> operand_stack;
        for (const std::string& token : postfix)
        {
            if (IsOperator(token))
            {
                auto operand_count = GetOperandCount(token);
                std::vector<BigNumber> operands;
                while (operand_count-- > 0)
                {
                    operands.push_back(operand_stack.top());
                    operand_stack.pop();
                }
                const BigNumber result = GetOperation(token)->handle(operands);
                operand_stack.push(result);
            }
            else
            {
                operand_stack.push(ToBigNumber(token));
            }
        }
        return operand_stack.top();
    }

    // Copy constructor
    BigNumberCalculator(const BigNumberCalculator& other)
    {
        // Iterate over the other object's operations map and make a copy of each unique_ptr
        for (const auto& pair : other.operations_)
        {
            auto& symbol = pair.first;
            auto& operation = pair.second;
            operations_[symbol] = operation->Clone();
        }
    }
    
    // Move constructor
	BigNumberCalculator(BigNumberCalculator&& other) noexcept
        : operations_(std::move(other.operations_))
    {
        // The other object's operations map has been moved to this object, so clear it in the other object
        other.operations_.clear();
    }

    // Copy assignment operator
    BigNumberCalculator& operator=(const BigNumberCalculator& other)
    {
        // Make a copy of the other object's operations map
        std::map<std::string, std::unique_ptr<Operation>> operations;
        for (const auto& pair : other.operations_)
        {
            auto& symbol = pair.first;
            auto& operation = pair.second;
            operations[symbol] = operation->Clone();
        }

        // Assign the copy to this object's operations map
        operations_ = std::move(operations);
        return *this;
    }

    // Move assignment operator
    BigNumberCalculator& operator=(BigNumberCalculator&& other) noexcept
    {
        // Move the other object's operations map to this object
        operations_ = std::move(other.operations_);
        // Clear the other object's operations map
        other.operations_.clear();
        return *this;
    }

	// output stream operator
    friend std::ostream& operator<<(std::ostream& out, const BigNumberCalculator& calculator)
    {
        // Print the result of the calculation as a string
        out << calculator.ToString();
        return out;
    }
};

#endif // !CISC187_MESA_BIG_NUMBER_CALCULATOR_H