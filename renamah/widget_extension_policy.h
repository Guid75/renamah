#ifndef WIDGET_EXTENSION_POLICY_H
#define WIDGET_EXTENSION_POLICY_H

#include "extension_policy.h"

#include "ui_widget_extension_policy.h"

class WidgetExtensionPolicy : public QWidget, private Ui::WidgetExtensionPolicy
{
	Q_OBJECT

public:
	WidgetExtensionPolicy(QWidget *parent = 0);

	const ExtensionPolicy &extensionPolicy() const { return _extensionPolicy; }
	void setExtensionPolicy(const ExtensionPolicy &policy);

signals:
	void extensionPolicyChanged();

protected:
	void changeEvent(QEvent *event);

private:
	ExtensionPolicy _extensionPolicy;

	void refreshControls();

private slots:
	void on_radioButtonFilterBasename_toggled(bool checked);
	void on_radioButtonFilterAll_toggled(bool checked);
	void on_radioButtonFilterExtension_toggled(bool checked);
	void on_radioButtonExtensionDefinitionLastPoint_toggled(bool checked);
	void on_radioButtonExtensionDefinitionFirstPoint_toggled(bool checked);
	void on_radioButtonExtensionDefinitionNthPoint_toggled(bool checked);
	void on_spinBoxExtensionNthPoint_valueChanged(int value);
	void on_pushButtonReset_clicked();
};

#endif
