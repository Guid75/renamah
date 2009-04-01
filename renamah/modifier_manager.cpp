#include "modifier_manager.h"

void ModifierManager::addFactory(core::ModifierFactory *factory)
{
	_factories << factory;
}

core::ModifierFactory *ModifierManager::factoryByName(const QString &name) const
{
	foreach (core::ModifierFactory *factory, _factories)
		if (!factory->info().name().compare(name, Qt::CaseInsensitive))
			return factory;
	return 0;
}
