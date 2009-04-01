#include "task_manager.h"

TaskManager *TaskManager::_instance = 0;

TaskManager &TaskManager::instance()
{
    if (!_instance)
        _instance = new TaskManager;

    return *_instance;
}
