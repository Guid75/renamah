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

#include <QMetaProperty>

#include "modifier.h"

namespace core {
	void Modifier::deserializeProperties(const QMap<QString,QPair<QString,QVariant> > &properties) {
		foreach (const QString &name, properties.keys()) {
			QString type = properties[name].first;
			QVariant value = properties[name].second;
			value.convert(QVariant::nameToType(qPrintable(type)));
			setProperty(qPrintable(name), value);
		}
	}

	QMap<QString,QPair<QString,QVariant> > Modifier::serializeProperties() {
		QMap<QString,QPair<QString,QVariant> > result;

		for (int i = 0; i < metaObject()->propertyCount(); ++i) {
			QMetaProperty metaproperty = metaObject()->property(i);
			const char *name = metaproperty.name();
			QVariant value = property(name);
			QString type(metaproperty.typeName());
			if (metaproperty.isEnumType())
				type = "int";
			result.insert(name, QPair<QString,QVariant>(type, value));
		}

		return result;
	}
}
