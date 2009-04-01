#ifndef ACTION_H
#define ACTION_H

class QString;

#include "modifier.h"

namespace core
{
	class Action : public Modifier
	{
		Q_OBJECT
	public:
		Action(QObject *parent = 0) : Modifier(parent) {}

		/*! Apply the action on the filename in argument */
		virtual void apply(const QString &fileName) const = 0;
	};
};

#endif
