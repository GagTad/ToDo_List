#pragma once
#include "ExecutionResult.h"
#include <string>

class ResponseFormatter {
public:
    static std::string format(const ExecutionResult& result);

private:
    static std::string translateStatus(TaskResult status, const std::string& taskName, const std::optional<std::string>& customMessage);
    static std::string formatTaskList(const std::vector<Task>& tasks);
};