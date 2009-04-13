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

#ifndef PROFILE_H
#define PROFILE_H

#include <QDomElement>

#include "extension_policy.h"

class Profile
{
public:
	static bool load(const QString &fileName);
	static bool save(const QString &fileName);

private:
	static void saveExtensionPolicy(QDomElement &root, const ExtensionPolicy &policy);
	static ExtensionPolicy loadExtensionPolicy(const QDomElement &policyElem);
};

#endif
