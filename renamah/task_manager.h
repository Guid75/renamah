 #ifndef TASK_MANAGER_H
 #define TASK_MANAGER_H

class TaskManager
{
public:
    static TaskManager &instance();

public:
    static TaskManager *_instance;
};

 #endif

