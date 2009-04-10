#include <QFileInfo>

#include <interfaces/filter_factory.h>

#include "filter_manager.h"
#include "filter_model.h"

FilterModel *FilterModel::_instance = 0;

FilterModel &FilterModel::instance()
{
	if (!_instance)
		_instance = new FilterModel;

	return *_instance;
}

FilterModel::FilterModel()
	: ModifierModel(&FilterManager::instance())
{
}

QString FilterModel::apply(const QString &filePath, int fileIndex) const
{
	QList<core::Filter*> filters;
	if (exclusiveModifier())
		filters << static_cast<core::Filter*>(exclusiveModifier());
	else
		foreach (core::Modifier *modifier, _modifiers)
		{
			if (_modifierStates[modifier])
				filters << static_cast<core::Filter*>(modifier);
		}

	QDir dir = QFileInfo(filePath).dir();
	QString tmpFilePath = filePath;
	foreach (core::Filter *filter, filters)
	{
		if (localExtensionPolicyStates[filter])
			tmpFilePath = localExtensionPolicies[filter].applyFilterOnFilePath(*filter, fileIndex, tmpFilePath, filePath);
		else
			tmpFilePath = _extensionPolicy.applyFilterOnFilePath(*filter, fileIndex, tmpFilePath, filePath);
	}

	return tmpFilePath;
}

void FilterModel::setExtensionPolicy(const ExtensionPolicy &policy)
{
	if (policy == _extensionPolicy)
		return;

	_extensionPolicy = policy;

	emit modifiersChanged();
}

bool FilterModel::isLocalExtensionPolicyEnabled(core::Filter *filter) const {
	return localExtensionPolicyStates[filter];
}

void FilterModel::setLocalExtensionPolicyEnabled(core::Filter *filter, bool state)
{
	localExtensionPolicyStates[filter] = state;
	emit modifiersChanged();
}

ExtensionPolicy FilterModel::localExtensionPolicy(core::Filter *filter) const
{
	return localExtensionPolicies[filter];
}

void FilterModel::setLocalExtensionPolicy(core::Filter *filter, const ExtensionPolicy &policy)
{
	QMap<core::Filter*, ExtensionPolicy>::iterator it = localExtensionPolicies.find(filter);
	if (it == localExtensionPolicies.end())
		localExtensionPolicies.insert(filter, policy);
	else
		*it = policy;
	emit modifiersChanged();
}

void FilterModel::clear() {
	localExtensionPolicies.clear();
	localExtensionPolicyStates.clear();
	_extensionPolicy = ExtensionPolicy();

	ModifierModel::clear();
}
