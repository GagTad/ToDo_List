#pragma once
#include "ParsedCommand.h"
#include "TaskManager.h"
#include "ExecutionResult.h"
#include <string>
#include <optional>

class Executor {
public:
    ExecutionResult execute(const ParsedCommand& command, TaskManager& manager);

private:
    std::optional<std::string> validate(const ParsedCommand& command);
};