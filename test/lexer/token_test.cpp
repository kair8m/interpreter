#include "gtest/gtest.h"
#include "lexer.h"

TEST(TokenTest, RawParsingTest)
{
    std::string code(
            "x = 5 + 3;"
    );
    auto&& tokens = Interpreter::Lexer::tokenize(code);
    EXPECT_TRUE(tokens.size() == 6);
    EXPECT_TRUE(tokens[0].getType() == Interpreter::Token::Type::VARIABLE);
    EXPECT_TRUE(tokens[0].getName() == "x");
    EXPECT_TRUE(tokens[1].getType() == Interpreter::Token::Type::OPERATOR_ASSIGNMENT);
    EXPECT_TRUE(tokens[2].getType() == Interpreter::Token::Type::CONSTANT);
    EXPECT_TRUE(std::abs(tokens[2].getVal() - 5) < std::numeric_limits<double>::epsilon());
    EXPECT_TRUE(tokens[3].getType() == Interpreter::Token::Type::OPERATOR_PLUS);
    EXPECT_TRUE(tokens[4].getType() == Interpreter::Token::Type::CONSTANT);
    EXPECT_TRUE(tokens[5].getType() == Interpreter::Token::Type::LINE_SEPARATOR);
    EXPECT_ANY_THROW(Interpreter::Lexer::tokenize("test = 1 = 2;"));
    EXPECT_ANY_THROW(Interpreter::Lexer::tokenize("= 1;"));
    EXPECT_ANY_THROW(Interpreter::Lexer::tokenize("= 1;"));
}