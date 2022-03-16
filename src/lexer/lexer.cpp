#include <algorithm>
#include <unordered_map>
#include "lexer.h"

static std::vector<std::string> split(const std::string& input, char delim, bool includeDelim);

static std::vector<std::string> split(const std::string& input, const std::vector<char>& delims, bool includeDelimeters)
{
    std::vector<std::string> output{input};
    auto copyDelims(delims);
    while (!copyDelims.empty())
    {
        std::vector<std::string> strVec;
        for (const auto& str: output)
        {
            auto splitResult = split(str, copyDelims.back(), includeDelimeters);
            for (const auto& res: splitResult)
                strVec.push_back(res);
        }
        output = strVec;
        copyDelims.pop_back();
    }
    return output;
}

static std::vector<std::string> split(const std::string& input, char delim, bool includeDelim)
{
    if (input.find(delim) == std::string::npos)
        return {input};

    std::vector<std::string> output;
    size_t pos = input.find(delim);
    size_t initialPos = 0;

    // Decompose statement
    while (pos != std::string::npos)
    {
        output.push_back(input.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;
        pos = input.find(delim, initialPos);
        if (includeDelim)
            output.emplace_back(1, delim);
    }

    // Add the last one
    output.push_back(input.substr(initialPos, std::min(pos, input.size()) - initialPos + 1));

    return output;
}

static void removeSpaces(std::string& input)
{
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
}

Interpreter::Token::Token(const std::string& input) : Interpreter::Token::Token(Interpreter::Token::Type::UNKNOWN)
{
    int spacePos = input.find(' ');
    if (spacePos > 0 && spacePos < input.size() - 1)
        throw std::string("invalid syntax");
    auto copy(input);
    removeSpaces(copy);
    m_type = determineType(copy);
}

Interpreter::Token::Type Interpreter::Token::determineType(const std::string& input)
{
    static const std::unordered_map<char, Interpreter::Token::Type> operatorMap = {
            {'+', Interpreter::Token::Type::OPERATOR_PLUS},
            {'-', Interpreter::Token::Type::OPERATOR_MINUS},
            {'*', Interpreter::Token::Type::OPERATOR_MULTIPLICATION},
            {'/', Interpreter::Token::Type::OPERATOR_DIVISION},
            {'^', Interpreter::Token::Type::OPERATOR_POWER},
            {'=', Interpreter::Token::Type::OPERATOR_ASSIGNMENT},
            {';', Interpreter::Token::Type::LINE_SEPARATOR},
    };
    if (input.size() == 1)
    {
        auto entry = operatorMap.find(input.front());
        if (entry != operatorMap.end())
            return entry->second;
    }
    if (isConstant(input))
        return Interpreter::Token::Type::CONSTANT;
    m_name = input;
    return Interpreter::Token::Type::VARIABLE;
}

bool Interpreter::Token::isConstant(const std::string& input)
{
    return (sscanf(input.c_str(), "%lf", &m_val) != 0);
}

static Interpreter::Tokens tokenizeStatement(const std::string& input)
{
    auto statement(input);
    removeSpaces(statement);
    if (statement.empty())
        return {};
    if (statement.front() == '=' || statement.back() == '=')
        throw std::string("invalid syntax");
    Interpreter::Tokens output;
    auto leftAndRight = split(statement, '=', true);
    if (leftAndRight.empty())
        return {}; // empty line
    if (leftAndRight.size() > 3)
        throw std::string("invalid syntax");
    auto left = leftAndRight[0];
    std::vector<char> operators;
    for (auto op: {'+', '-', '*', '/', '^'})
    {
        if (leftAndRight[0].find(op) != std::string::npos)
            operators.push_back(op);
    }
    auto expressions = split(left, operators, true);
    for (const auto& expr: expressions)
    {
        output.push_back(Interpreter::Token(expr));
    }

    if (leftAndRight.size() == 3)
    {
        output.push_back(Interpreter::Token(Interpreter::Token::Type::OPERATOR_ASSIGNMENT));
        auto tokens = tokenizeStatement(leftAndRight[2]);
        for (const auto& token: tokens)
            output.push_back(token);
    }

    return output;
}

Interpreter::Tokens Interpreter::Lexer::tokenize(const std::string& expr)
{
    if (expr.empty())
        return {};
    Tokens output;
    auto statements = split(expr, ';', true);
    for (const auto& statement: statements)
    {
        for (const auto& token: tokenizeStatement(statement))
            output.push_back(token);
    }
    return output;
}
