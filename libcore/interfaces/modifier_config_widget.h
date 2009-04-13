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

#ifndef MODIFIER_CONFIG_WIDGET_H
#define MODIFIER_CONFIG_WIDGET_H

#include <QWidget>
#include <QEvent>

#include "modifier.h"

namespace core
{
	class ModifierConfigWidget : public QWidget
	{
		Q_OBJECT

	public:
		ModifierConfigWidget(QWidget *parent = 0)
			: QWidget(parent),
			  _modifier(0),
			  languageChanging(false) {}

		Modifier *modifier() const { return _modifier; }
		void setModifier(Modifier *modifier);

	protected:
		virtual void changeEvent(QEvent *event);
		virtual void languageChanged() {}

		bool isLanguageChanging() const { return languageChanging; }

	protected slots:
		virtual void refreshControls() = 0; //!< Is called at every modifier settings changed and after setModifier()

	private:
		Modifier *_modifier;
		bool languageChanging;
	};
};

#endif											\


