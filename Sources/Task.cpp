#include "Task.h"

Task::Task(const std::string& name)
    : m_name(name), m_isCompleted(false) {
}

const std::string& Task::getName() const {
    return m_name;
}

bool Task::isCompleted() const {
    return m_isCompleted;
}

void Task::setCompleted(bool completed) {
    m_isCompleted = completed;
}