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

#ifndef MODIFIER_H
#define MODIFIER_H

#include <QObject>
#include <QMap>
#include <QPair>
#include <QVariant>

#include "plugin.h"

namespace core
{
	class ModifierFactory;

	class Modifier : public QObject
	{
		Q_OBJECT

	public:
		Modifier(QObject *parent = 0) : QObject(parent) {}

		friend class ModifierFactory;

		/*! \return a resume string of the modifier action */
		virtual QString resume() const = 0;

		/*! \return the factory which generates the modifier */
		ModifierFactory *factory() const { return _factory; }

		/*! \return a map which contains all serializable properties of the modifier */
		QMap<QString,QPair<QString,QVariant> > serializeProperties();

		/*! Fill the object properties */
		void deserializeProperties(const QMap<QString,QPair<QString,QVariant> > &properties);

	signals:
		/** Emitted when modifier settings changing, before new value is affected. */
		void settingsChanging();
		/** Emitted when modifier settings changed */
		void settingsChanged();

	private:
		ModifierFactory *_factory;
	};
};

#endif
