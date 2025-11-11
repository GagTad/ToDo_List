#include "Executor.h"
#include "ResponseFormatter.h"
#include <fstream>
#include "Lexer.h"
#include "Parser.h"

ExecutionResult Executor::execute(const ParsedCommand& command, TaskManager& manager) {
    if (auto error = validate(command); error.has_value()) {
        return { TaskResult::ErrorSemantic, std::nullopt, std::nullopt, *error };
    }

    switch (command.type) {
    case CommandType::ADD_TASK: {
        const std::string& name = command.arguments.at("-name");
        TaskResult status = manager.addTask(name);
        return { status, name, std::nullopt, std::nullopt };
    }
    case CommandType::REMOVE_TASK: {
        const std::string& name = command.arguments.at("-name");
        TaskResult status = manager.removeTask(name);
        return { status, name, std::nullopt, std::nullopt };
    }
    case CommandType::COMPLETE_TASK: {
        const std::string& name = command.arguments.at("-name");
        TaskResult status = manager.completeTask(name);
        return { status, name, std::nullopt, std::nullopt };
    }
    case CommandType::LIST_TASKS: {
        auto tasks = manager.listTasks();
        return { TaskResult::Success, std::nullopt, tasks, std::nullopt };
    }
    case CommandType::EXECUTE_FILE: {
        const std::string& path = command.arguments.at("-file_path");
        std::ifstream file(path);
        if (!file) {
            return { TaskResult::ErrorFileOpen, path, std::nullopt, std::nullopt };
        }

        std::string full_log;
        std::string line;
        int line_num = 1;

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                line_num++;
                continue;
            }

            std::string line_result_text;
            try {
                Lexer lineLexer(line);
                Parser lineParser(lineLexer.tokenize());
                ParsedCommand lineCommand = lineParser.parse();
                ExecutionResult line_result = this->execute(lineCommand, manager);
                line_result_text = ResponseFormatter::format(line_result);
            }
            catch (const std::exception& e) {
                line_result_text = std::string("<font color='red'> Error: ") + e.what();
            }

            full_log += "[" + std::to_string(line_num) + "] > " + line + "\n";
            full_log += "    " + line_result_text + "\n";
            line_num++;
        }
        return { TaskResult::BatchExecutionCompleted, std::nullopt, std::nullopt, full_log };
    }
    case CommandType::UNKNOWN:
    default: {
        return { TaskResult::ErrorUnknown, std::nullopt, std::nullopt, "<font color='red'> Executor cannot handle this command type." };
    }
    }
}

std::optional<std::string> Executor::validate(const ParsedCommand& command) {
    switch (command.type) {
    case CommandType::ADD_TASK:
    case CommandType::REMOVE_TASK:
    case CommandType::COMPLETE_TASK:
        if (command.arguments.count("-name") == 0) {
            return "<font color='red'> Missing '-name' argument.";
        }
        break;

    case CommandType::EXECUTE_FILE:
        if (command.arguments.count("-file_path") == 0) {
            return "<font color='red'> Missing '-file_path' argument.";
        }
        break;

    case CommandType::LIST_TASKS:
        if (!command.arguments.empty()) {
            return "<font color='red'> 'list_tasks' does not take any arguments.";
        }
        break;
    case CommandType::UNKNOWN:
        return "<font color='red'> Command not recognized.";
    default:
        break;
    }
    return std::nullopt;
}
