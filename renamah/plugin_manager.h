#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <QObject>
#include <QStringList>

class PluginManager
{
public:
	static PluginManager &instance();

	void load();

	const QStringList &pluginFileNames() const { return _pluginFileNames; }

private:
	static PluginManager *_instance;

	QStringList _pluginFileNames;

	void dispatchPlugin(QObject *plugin);
};

#endif
