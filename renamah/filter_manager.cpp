#include "filter_manager.h"

FilterManager *FilterManager::_instance = 0;

FilterManager &FilterManager::instance()
{
	if (!_instance)
          _instance = new FilterManager;

     return *_instance;
}
