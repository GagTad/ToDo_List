#include "Parser.h"

const std::map<std::string, CommandType> Parser::command_map = {
    {"add_task", CommandType::ADD_TASK},
    {"remove_task", CommandType::REMOVE_TASK},
    {"complete_task", CommandType::COMPLETE_TASK},
    {"list_tasks", CommandType::LIST_TASKS},
    {"execute_file", CommandType::EXECUTE_FILE}
};

Parser::Parser(const std::vector<Token>& tokens)
    :m_tokens(tokens), m_position(0) 
{
    if (!m_tokens.empty()) {
		m_currentToken = m_tokens[m_position];
    }
}

void Parser::advance()
{
    m_position++;
    if (m_position < m_tokens.size()){
        m_currentToken = m_tokens[m_position];
    }
}

void Parser::consume(TokenType type, const std::string& errorMessage)
{
    if (m_currentToken.type == type) {
        advance();
    }
    else {
        throw std::runtime_error(errorMessage);
    }
}

//command->argument->string literal->
ParsedCommand Parser::parse()
{
    ParsedCommand cmd;
    if (m_currentToken.type != TokenType::COMMAND) {
        throw std::runtime_error("Syntax Error: Expected a command at the beginning.");
    }
    auto it = command_map.find(m_currentToken.value);
    if (it != command_map.end()) {
        cmd.type = it->second;
    }
    advance();
    //argiuments 
    while (m_currentToken.type != TokenType::END_OF_INPUT) {
        if (m_currentToken.type != TokenType::KEYWORD) {
            throw std::runtime_error("Syntax Error: Expected a keyword  for an argument.");
        }
        std::string key = m_currentToken.value;
        advance();
        //keyword->string literal
        consume(TokenType::STRING_LITERAL, "Syntax Error: Expected a value in {braces} after keyword '" + key + "'.");
        std::string value = m_tokens[m_position - 1].value;
        cmd.arguments[key] = value;
    }
    return cmd;
}