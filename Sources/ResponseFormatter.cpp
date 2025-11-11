#include "ResponseFormatter.h"
#include <sstream>
#include <iostream>

std::string ResponseFormatter::format(const ExecutionResult& result) {
    if (result.status == TaskResult::BatchExecutionCompleted) {
        return result.customMessage.value_or("Batch execution completed, but no log was generated.");
    }

    if (result.taskList.has_value()) {
        if (result.taskList->empty()) {
            return "No tasks listed.";
        }
        return formatTaskList(*result.taskList);
    }

    std::string taskName = result.taskName.value_or("");
    return translateStatus(result.status, taskName, result.customMessage);
}

std::string ResponseFormatter::translateStatus(TaskResult status, const std::string& taskName, const std::optional<std::string>& customMessage) {
    std::string quotedName = "'" + taskName + "'";

    switch (status) {
    case TaskResult::Success:               return "<font color='green'>Task " + quotedName + " added successfully.";
    case TaskResult::SuccessRemoved:        return "<font color='green'>Task " + quotedName + " was removed.";
    case TaskResult::SuccessCompleted:      return "<font color='green'>Task " + quotedName + " marked as completed.";
    case TaskResult::InfoAlreadyCompleted:  return "<font color='orange'>Info: Task " + quotedName + " was already completed.";
    case TaskResult::ErrorNotFound:         return "<font color='red'>Error: Task " + quotedName + " not found.";
    case TaskResult::ErrorAlreadyExists:    return "<font color='red'>Error: A task with the name " + quotedName + " already exists.";
    case TaskResult::ErrorFileOpen:         return "<font color='red'>Error: Could not open file " + quotedName + ".";
    case TaskResult::ErrorSemantic:         return "<font color='red'>Semantic Error: " + customMessage.value_or("The command has a semantic error.");
    case TaskResult::ErrorUnknown:          return "<font color='red'>Error: An unknown error occurred.";
    case TaskResult::BatchExecutionCompleted: return "Batch execution completed."; // Should be handled by batchLog
    default:                                return "<font color='red'>Internal Error: No translation for this result code.";
    }
}

std::string ResponseFormatter::formatTaskList(const std::vector<Task>& tasks) {
    std::stringstream ss;
    ss << tasks.size() << " tasks listed:\n";
    for (const auto& task : tasks) {
        ss << (task.isCompleted() ? "[x] " : "[ ] ") << task.getName() << "\n";
    }
    std::string resultStr = ss.str();
    if (!resultStr.empty()) {
        resultStr.pop_back(); // Remove trailing newline
    }
    return resultStr;
}
