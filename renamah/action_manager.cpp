#include "action_manager.h"

ActionManager *ActionManager::_instance = 0;

ActionManager &ActionManager::instance()
{
     if (!_instance)
          _instance = new ActionManager;

     return *_instance;
}
