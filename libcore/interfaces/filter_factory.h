#ifndef FILTER_FACTORY_H
#define FILTER_FACTORY_H

#include "modifier_factory.h"
#include "filter.h"

namespace core
{
	class FilterFactory : public ModifierFactory
	{
	protected:
		Modifier *createModifier() const { return createFilter(); }

		/*! True method to create a new filter */
		virtual Filter *createFilter() const = 0;
	};
};

Q_DECLARE_INTERFACE(core::FilterFactory,
                    "fr.free.guillaume.denry.Renamah.FilterFactory/1.0")

#endif
