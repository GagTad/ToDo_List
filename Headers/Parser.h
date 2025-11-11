#pragma once
#include "Token.h"
#include "ParsedCommand.h"
#include <vector>
#include <stdexcept>
#include <map>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    ParsedCommand parse();

private:
    void advance();
    void consume(TokenType type, const std::string& errorMessage);

    std::vector<Token> m_tokens;
    size_t m_position;
    Token m_currentToken;

    static const std::map<std::string, CommandType> COMMAND_MAP;
};