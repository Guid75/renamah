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


