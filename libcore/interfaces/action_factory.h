#ifndef ACTION_FACTORY_H
#define ACTION_FACTORY_H

#include "modifier_factory.h"
#include "action.h"

namespace core
{
	class ActionFactory : public ModifierFactory
	{
	protected:
		Modifier *createModifier() const { return createAction(); }

		/*! True method to create a new filter */
		virtual Action *createAction() const = 0;
	};
};

Q_DECLARE_INTERFACE(core::ActionFactory,
                    "fr.free.guillaume.denry.Renamah.ActionFactory/1.0")

#endif
