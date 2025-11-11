#pragma once
#include "Token.h"
#include <string>
#include <vector>
#include <map>

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    void advance();
    void skipWhitespace();
    Token getNextToken();
    Token makeIdentifier();
    Token makeStringLiteral();

    std::string m_input;
    size_t m_position;

    static const std::map<std::string, TokenType> RESERVED_WORDS;
};