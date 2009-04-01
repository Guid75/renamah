#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include "modifier_manager.h"

class ActionManager : public ModifierManager
{
public:
	static ActionManager &instance();

	QString modifierTypeName() { return QObject::tr("action"); }

private:
	static ActionManager *_instance;
};

#endif
