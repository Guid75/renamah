#ifndef FILTER_MODEL_H
#define FILTER_MODEL_H

#include <QDir>

#include "extension_policy.h"
#include "modifier_model.h"

class FilterModel : public ModifierModel
{
	Q_OBJECT

public:
	static FilterModel &instance();

	/*! Returns the filtered result of the file path parameter */
	QString apply(const QString &filePath, int fileIndex) const;

	void clear();

	const ExtensionPolicy &extensionPolicy() const { return _extensionPolicy; }
	void setExtensionPolicy(const ExtensionPolicy &policy);

	bool isLocalExtensionPolicyEnabled(core::Filter *filter) const;
	void setLocalExtensionPolicyEnabled(core::Filter *filter, bool state);

	ExtensionPolicy localExtensionPolicy(core::Filter *filter) const;
	void setLocalExtensionPolicy(core::Filter *filter, const ExtensionPolicy &policy);

private:
	FilterModel();

	static FilterModel *_instance;

	ExtensionPolicy _extensionPolicy;
	QMap<core::Filter*, ExtensionPolicy> localExtensionPolicies;
	QMap<core::Filter*, bool> localExtensionPolicyStates;
};

#endif
