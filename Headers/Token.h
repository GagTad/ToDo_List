#pragma once
#include <string>

enum class TokenType {
    COMMAND,
    KEYWORD,
    STRING_LITERAL,
    UNKNOWN,
    END_OF_INPUT
};

struct Token {
    TokenType type;
    std::string value;
};