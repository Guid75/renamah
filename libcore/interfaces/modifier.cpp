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
