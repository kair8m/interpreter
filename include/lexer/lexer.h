#pragma once

#include <vector>
#include <string>

namespace Interpreter
{
class Token
{
public:
    enum class Type
    {
        UNKNOWN,
        VARIABLE,
        OPERATOR_ASSIGNMENT,
        OPERATOR_PLUS,
        OPERATOR_MINUS,
        OPERATOR_MULTIPLICATION,
        OPERATOR_DIVISION,
        OPERATOR_POWER,
        LINE_SEPARATOR,
        CONSTANT,
    };

    explicit Token(Type type) : m_type(type), m_val(0), m_name()
    {}

    explicit Token(const std::string& input);

    Type getType() const { return m_type; }

    double getVal() const { return m_val; }

    const std::string& getName() const { return m_name; }

private:
    Type determineType(const std::string&);

    bool isConstant(const std::string& input);

private:
    Type m_type;
    double m_val;
    std::string m_name;
};

using Tokens = std::vector<Token>;

namespace Lexer
{
Tokens tokenize(const std::string& expr);
}
}