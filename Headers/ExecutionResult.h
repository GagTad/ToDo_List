#pragma once
#include "TaskManager.h"
#include <string>
#include <vector>
#include <optional>

struct ExecutionResult {
    TaskResult status;
    std::optional<std::string> taskName;
    std::optional<std::vector<Task>> taskList;
    std::optional<std::string> customMessage; // For semantic errors and batch logs
};