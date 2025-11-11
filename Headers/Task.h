#pragma once
#include <string>

class Task {
public:
    explicit Task(const std::string& name);

    const std::string& getName() const;
    bool isCompleted() const;
    void setCompleted(bool completed);

private:
    std::string m_name;
    bool m_isCompleted;

};
