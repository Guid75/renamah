#ifndef PLUGIN_INFO_H
#define PLUGIN_INFO_H

#include <QString>

namespace core
{
     class PluginInfo
     {
	 public:
		 PluginInfo(const QString &name,
					const QString &caption,
					const QString &description = "",
					const QString &author = "") :
			 _name(name), _caption(caption), _description(description), _author(author) {}

		 const QString &name() const { return _name; }
		 const QString &caption() const { return _caption; }
		 const QString &description() const { return _description; }
		 const QString &author() const { return _author; }

	 private:
          QString _name;
          QString _caption;
          QString _description;
          QString _author;
     };
}

#endif
