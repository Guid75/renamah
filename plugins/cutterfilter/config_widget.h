#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <interfaces/modifier_config_widget.h>

#include "cutter_filter.h"
#include "ui_config_widget.h"

class ConfigWidget : public core::ModifierConfigWidget, private Ui::ConfigWidget
{
     Q_OBJECT

public:
     ConfigWidget();

private:
	CutterFilter *filter() { return static_cast<CutterFilter*>(modifier()); }

protected:
	void languageChanged();

protected slots:
	void refreshControls();

private slots:
	void on_spinBoxStartMarker_valueChanged(int value);
	void on_comboBoxStartMarkerPosition_currentIndexChanged(int index);
	void on_spinBoxEndMarker_valueChanged(int value);
	void on_comboBoxEndMarkerPosition_currentIndexChanged(int index);
	void on_radioButtonKeep_toggled(bool checked);
	void on_radioButtonRemove_toggled(bool checked);
};

#endif
