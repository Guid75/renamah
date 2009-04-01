#ifndef FILTER_MANAGER_H
#define FILTER_MANAGER_H

#include "modifier_manager.h"

class FilterManager : public ModifierManager
{
public:
	static FilterManager &instance();

	QString modifierTypeName() { return QObject::tr("filter"); }

private:
     static FilterManager *_instance;
};

#endif
