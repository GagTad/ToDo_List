#include "Lexer.h"
#include <cctype>

const std::map<std::string, TokenType> Lexer::RESERVED_WORDS = {
    {"add_task", TokenType::COMMAND},
    {"remove_task", TokenType::COMMAND},
    {"complete_task", TokenType::COMMAND},
    {"list_tasks", TokenType::COMMAND},
    {"execute_file", TokenType::COMMAND},
    {"-name", TokenType::KEYWORD},
    {"-file_path", TokenType::KEYWORD}
};

Lexer::Lexer(const std::string& input) : m_input(input), m_position(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token = getNextToken();
    while (token.type != TokenType::END_OF_INPUT) {
        tokens.push_back(token);
        token = getNextToken();
    }
    tokens.push_back(token);
    return tokens;
}

void Lexer::advance() {
    m_position++;
}

void Lexer::skipWhitespace() {
    while (m_position < m_input.length() && std::isspace(m_input[m_position])) {
        advance();
    }
}

Token Lexer::makeIdentifier() {
    size_t start = m_position;
    while (m_position < m_input.length() && (std::isalnum(m_input[m_position]) || m_input[m_position] == '_' || m_input[m_position] == '-')) {
        advance();
    }
    std::string value = m_input.substr(start, m_position - start);

    auto it = RESERVED_WORDS.find(value);
    if (it != RESERVED_WORDS.end()) {
        return { it->second, value };
    }
    return { TokenType::UNKNOWN, value };
}

Token Lexer::makeStringLiteral() {
    advance(); // Skip '{'
    size_t start = m_position;
    while (m_position < m_input.length() && m_input[m_position] != '}') {
        advance();
    }

    if (m_position >= m_input.length()) {
        return { TokenType::UNKNOWN, "Unterminated string literal" };
    }

    std::string value = m_input.substr(start, m_position - start);
    advance(); // Skip '}'
    return { TokenType::STRING_LITERAL, value };
}

Token Lexer::getNextToken() {
    while (m_position < m_input.length()) {
        char currentChar = m_input[m_position];

        if (std::isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (currentChar == '{') {
            return makeStringLiteral();
        }

        if (std::isalpha(currentChar) || currentChar == '-') {
            return makeIdentifier();
        }

        advance();
        return { TokenType::UNKNOWN, std::string(1, currentChar) };
    }

    return { TokenType::END_OF_INPUT, "" };
}