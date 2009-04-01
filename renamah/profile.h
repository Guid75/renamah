#ifndef PROFILE_H
#define PROFILE_H

#include <QDomElement>

#include "extension_policy.h"

class Profile
{
public:
	static bool load(const QString &fileName);
	static bool save(const QString &fileName);

private:
	static void saveExtensionPolicy(QDomElement &root, const ExtensionPolicy &policy);
	static ExtensionPolicy loadExtensionPolicy(const QDomElement &policyElem);
};

#endif
