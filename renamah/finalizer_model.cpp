#include <interfaces/action.h>

#include "finalizer_model.h"

FinalizerModel *FinalizerModel::_instance = 0;

FinalizerModel &FinalizerModel::instance()
{
	if (!_instance)
		_instance = new FinalizerModel;

	return *_instance;
}

FinalizerModel::FinalizerModel()
	: ModifierModel()
{
}

void FinalizerModel::apply(const QString &fileName) const
{
	if (exclusiveModifier())
	{
		static_cast<core::Action*>(exclusiveModifier())->apply(fileName);
		return;
	}

	foreach (core::Modifier *modifier, _modifiers)
	{
		core::Action *action = static_cast<core::Action*>(modifier);
		if (_modifierStates[modifier])
		{
			action->apply(fileName);
		}
	}
}

