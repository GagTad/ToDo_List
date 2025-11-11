#pragma once
#include <string>
#include <map>

enum class CommandType {
    ADD_TASK,
    REMOVE_TASK,
    COMPLETE_TASK,
    LIST_TASKS,
    EXECUTE_FILE,
    UNKNOWN
};

struct ParsedCommand {
    CommandType type = CommandType::UNKNOWN;
    std::map<std::string, std::string> arguments;
};