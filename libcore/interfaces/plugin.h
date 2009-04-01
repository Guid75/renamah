#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_info.h"

namespace core
{
	class Plugin
	{
	public:
		/*! Returns all infos relatives to the plugin (name, author, etc) */
		virtual PluginInfo info() const = 0;
	};
};

#endif
