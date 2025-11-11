#include "Parser.h"

const std::map<std::string, CommandType> Parser::COMMAND_MAP = {
    {"add_task", CommandType::ADD_TASK},
    {"remove_task", CommandType::REMOVE_TASK},
    {"complete_task", CommandType::COMPLETE_TASK},
    {"list_tasks", CommandType::LIST_TASKS},
    {"execute_file", CommandType::EXECUTE_FILE}
};

Parser::Parser(const std::vector<Token>& tokens)
    : m_tokens(tokens), m_position(0) {
    if (!m_tokens.empty()) {
        m_currentToken = m_tokens[m_position];
    }
}

void Parser::advance() {
    m_position++;
    if (m_position < m_tokens.size()) {
        m_currentToken = m_tokens[m_position];
    }
}

void Parser::consume(TokenType type, const std::string& errorMessage) {
    if (m_currentToken.type == type) {
        advance();
    }
    else {
        throw std::runtime_error(errorMessage);
    }
}

ParsedCommand Parser::parse() {
    ParsedCommand cmd;

    if (m_currentToken.type != TokenType::COMMAND) {
        throw std::runtime_error("<font color='red'> Syntax Error: Expected a command at the beginning.");
    }

    auto it = COMMAND_MAP.find(m_currentToken.value);
    if (it != COMMAND_MAP.end()) {
        cmd.type = it->second;
    }
    else {
        cmd.type = CommandType::UNKNOWN; // Handle unknown commands gracefully
    }
    advance();

    while (m_currentToken.type != TokenType::END_OF_INPUT) {
        if (m_currentToken.type != TokenType::KEYWORD) {
            throw std::runtime_error("<font color='red'> Syntax Error: Expected a keyword (e.g., '-name') for an argument.");
        }
        std::string key = m_currentToken.value;
        advance();

        consume(TokenType::STRING_LITERAL, "<font color='red'> Syntax Error: Expected a value in {braces} after keyword '" + key + "'.");

        std::string value = m_tokens[m_position - 1].value;

        cmd.arguments[key] = value;
    }

    return cmd;
}
