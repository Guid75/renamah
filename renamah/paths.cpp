/*
 * Renamah
 * Copyright (C) 2009 Guillaume Denry <guillaume.denry@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDir>
#include <QCoreApplication>
#include <QDesktopServices>

#include "global.h"

#include "paths.h"

QString Paths::sharePath()
{
    QDir appDir(QCoreApplication::applicationDirPath());

    if (Global::devMode())
        return QDir(appDir.filePath("../share/renamah")).canonicalPath();

    if (Global::localMode())
        return appDir.absolutePath();


#if defined(Q_OS_LINUX)
    return QDir(appDir.filePath("/usr/share/renamah")).canonicalPath();
#else
    return appDir.absolutePath();
#endif
}

QString Paths::libPath()
{
    QDir appDir(QCoreApplication::applicationDirPath());

    if (Global::devMode()) {
        return QDir(appDir.filePath("../lib/renamah")).canonicalPath();
    }

    if (Global::localMode())
        return appDir.absolutePath();


#if defined(Q_OS_LINUX)
    return QDir(appDir.filePath("/usr/lib/renamah")).canonicalPath();
#else
    return appDir.absolutePath();
#endif
}

QString Paths::profilePath()
{
    if (Global::devMode() || Global::localMode())
        return QDir(QCoreApplication::applicationDirPath()).filePath(qApp->applicationName());

    return QDesktopServices::storageLocation(QDesktopServices::DataLocation);
}
