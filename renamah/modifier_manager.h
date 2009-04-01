#ifndef MODIFIER_MANAGER_H
#define MODIFIER_MANAGER_H

#include <interfaces/modifier_factory.h>

class ModifierManager
{
public:
     void addFactory(core::ModifierFactory *factory);

     core::ModifierFactory *factoryByName(const QString &name) const;

     const QList<core::ModifierFactory*> &factories() const { return _factories; }

	/*! Returns the type name of the modifier created by the factory */
	virtual QString modifierTypeName() = 0;

private:
     QList<core::ModifierFactory*> _factories;
};

#endif
