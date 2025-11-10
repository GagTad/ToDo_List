#include <cctype>
#include "Lexer.h"


const std::map<std::string, TokenType> Lexer::reserved_words = {
    {"add_task", TokenType::COMMAND},
    {"remove_task", TokenType::COMMAND},
    {"complete_task", TokenType::COMMAND},
    {"list_tasks", TokenType::COMMAND},
    {"execute_file", TokenType::COMMAND},
    {"-name", TokenType::KEYWORD},
    {"-file_path", TokenType::KEYWORD}
};

Lexer::Lexer(const std::string& input)
    :m_input(input), m_position(0) {}



std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    Token token = getNextToken();
    while (token.type != TokenType::END_OF_INPUT)
    {
        tokens.push_back(token);
        token = getNextToken();
    }
    tokens.push_back(token);
    return tokens;
}

void Lexer::advance()
{
    m_position++;
}

char Lexer::peek() const
{
    if (m_position + 1 >= m_input.length())
        return '\0';
    return m_input[m_position + 1];
}

void Lexer::skipWhitespace()
{
    while (m_position < m_input.length() && std::isspace(m_input[m_position])) {
        advance();
    }
}

Token Lexer::makeIdentifier()
{
    size_t start = m_position;
    while (m_position < m_input.length() && (std::isalnum(m_input[m_position]) || m_input[m_position] == '_' || m_input[m_position] == '-')) {
        advance();
    }

	std::string value = m_input.substr(start, m_position - start);
	auto it = reserved_words.find(value);
	if (it != reserved_words.end()) {
		return { it->second, value };
	}
	return { TokenType::UNKNOWN, value };
}

Token Lexer::makeStringLiteral()
{
    advance();
    size_t start = m_position;
    while (m_position < m_input.length() && m_input[m_position] != '}') {
        advance();
    }
    if (m_position >= m_input.length()) {
        return { TokenType::UNKNOWN, "Unterminated string literal" };
    }
    std::string value = m_input.substr(start, m_position - start);
    advance(); 
    return { TokenType::STRING_LITERAL, value };

}

Token Lexer::getNextToken()
{
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



