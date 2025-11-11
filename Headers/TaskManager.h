#pragma once

#include <map>
#include <vector>
#include <utility>
#include <string>
#include "Task.h"

enum class TaskResult {
    Success,                 
    SuccessRemoved,          
    SuccessCompleted,        
    BatchExecutionCompleted,  // Ֆայլից հրամանների կատարումն ավարտվել է

    ErrorNotFound,           
    ErrorAlreadyExists,       
    ErrorFileOpen,            
    ErrorSemantic,           
    ErrorUnknown,            

    InfoAlreadyCompleted
};

class TaskManager
{
public:
	TaskResult addTask(const std::string& name);
	TaskResult removeTask(const std::string& name);
	TaskResult completeTask(const std::string& name);
	std::vector<Task> listTasks() const;


private:
	std::map<std::string, Task> m_tasks;
};

