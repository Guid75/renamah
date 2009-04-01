#ifndef MODIFIER_FACTORY_H
#define MODIFIER_FACTORY_H

#include "plugin.h"
#include "modifier.h"
#include "modifier_config_widget.h"

namespace core
{
	class ModifierFactory : public Plugin
	{
	public:
		/*! Make a new modifier. Just a call to createModifier() and some parentality done */
		Modifier *makeModifier() const {
			Modifier *modifier = createModifier();
			modifier->_factory = const_cast<ModifierFactory*>(this);
			return modifier;
		}

		/*! Returns a configuration QWidget */
		virtual ModifierConfigWidget *makeConfigurationWidget(Modifier *modifier) const { return 0; }

		/*! Deletes the configuration widget in argument (mandatory for shared lib) */
		virtual void deleteConfigurationWidget(QWidget *widget) const { delete widget; }

	protected:
		/*! True method to create a new modifier */
		virtual Modifier *createModifier() const = 0;
	};
};

#endif
