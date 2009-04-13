/*
 * Renamah
 * Copyright (C) 2009 Guillaume Denry <guillaume.denry@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
