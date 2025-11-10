#include "TaskManager.h"

TaskResult TaskManager::addTask(const std::string& name)
{
    auto [iterator, success] = m_tasks.emplace(name, Task(name));

    if (success)
    {
        return TaskResult::Success;
    }
    else {
		return TaskResult::ErrorAlreadyExists;
    }
}

TaskResult TaskManager::removeTask(const std::string& name)
{
    if (m_tasks.erase(name) > 0)
    {
        return TaskResult::SuccessRemoved;
	}
    else {
        return TaskResult::ErrorNotFound;
    }
}

TaskResult TaskManager::completeTask(const std::string& name)
{
	auto it = m_tasks.find(name);
    if (it == m_tasks.end())
    {
		return TaskResult::ErrorNotFound;
    }
    if(it->second.isCompleted())
    {
		return TaskResult::InfoAlreadyCompleted;
    }
	it->second.setCompleted(true);
	return TaskResult::SuccessCompleted;
}

std::vector<Task> TaskManager::listTasks() const
{
    std::vector<Task> taskList;
    taskList.reserve(m_tasks.size());

    for (const auto& pair : m_tasks)
    {
		taskList.push_back(pair.second);
    }
	return taskList;
}
