#include "modifier_config_widget.h"

namespace core
{
	void ModifierConfigWidget::setModifier(Modifier *modifier) {
		if (_modifier == modifier)
			return;

		_modifier = modifier;

		connect(_modifier, SIGNAL(settingsChanged()), this, SLOT(refreshControls()));

		// Need a refresh for the first time
		refreshControls();
	}

	void ModifierConfigWidget::changeEvent(QEvent *event) {
		if (event->type() == QEvent::LanguageChange) {
			languageChanging = true;
			languageChanged();
			languageChanging = false;
		} else
			QWidget::changeEvent(event);
	}
};
