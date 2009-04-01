#include <QPluginLoader>
#include <QDir>
#include <QCoreApplication>

#include <interfaces/filter.h>
#include <interfaces/filter_factory.h>
#include <interfaces/action_factory.h>

#include "filter_manager.h"
#include "action_manager.h"
#include "plugin_manager.h"

PluginManager *PluginManager::_instance = 0;

PluginManager &PluginManager::instance()
{
     if (!_instance)
          _instance = new PluginManager;

     return *_instance;
}

void PluginManager::load()
{
	// Static plugins
	foreach (QObject *plugin, QPluginLoader::staticInstances())
		dispatchPlugin(plugin);

	// Dynamic plugins
	QDir pluginsDir(QDir(QCoreApplication::applicationDirPath()).filePath("plugins"));
	foreach (const QString &fileName, pluginsDir.entryList(QDir::Files))
	{
		if (QLibrary::isLibrary(fileName)) {
			QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
			QObject *plugin = loader.instance();
			if (plugin) {
				dispatchPlugin(plugin);
				_pluginFileNames << pluginsDir.absoluteFilePath(fileName);
			}
			else
				qDebug("Error: %s", qPrintable(loader.errorString()));
		}
	}
}

void PluginManager::dispatchPlugin(QObject *plugin)
{
	Q_ASSERT_X(plugin, "PluginManager::dispatchPlugin()", "<plugin> is 0!");

	core::ModifierFactory *factory = qobject_cast<core::FilterFactory*>(plugin);
	if (factory)
	{
		FilterManager::instance().addFactory(factory);
		return;
	}

	factory = qobject_cast<core::ActionFactory*>(plugin);
	if (factory)
	{
		ActionManager::instance().addFactory(factory);
		return;
	}
}
