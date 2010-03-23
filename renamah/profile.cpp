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

#include <QDomDocument>
#include <QTextStream>
#include <QMetaProperty>

#include <interfaces/modifier_factory.h>

#include "filter_model.h"
#include "finalizer_model.h"
#include "filter_manager.h"
#include "profile.h"

bool Profile::load(const QString &fileName) {
    QDomDocument doc("renamah_profile");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical("Cannot open the profile file");
        return false;
    }
    if (!doc.setContent(&file)) {
        qCritical("Error in the XML scheme");
        file.close();
        return false;
    }
    file.close();

    QDomElement rootElem = doc.firstChildElement("profile");
    if (rootElem.isNull()) {
        qCritical("Error in format of the profile file");
        return false;
    }

    FilterModel::instance().clear();

    QDomElement extensionPolicyElem = rootElem.firstChildElement("extension_policy");
    if (!extensionPolicyElem.isNull())
        FilterModel::instance().setExtensionPolicy(loadExtensionPolicy(extensionPolicyElem));

    // Filters
    QDomElement filtersElem = rootElem.firstChildElement("filters");
    if (!filtersElem.isNull()) {
        QDomElement filterElem = filtersElem.firstChildElement("modifier");
        while (!filterElem.isNull()) {
            QString factoryName = filterElem.attribute("factory");
            core::ModifierFactory *factory = FilterManager::instance().factoryByName(factoryName);
            if (factory) {
                core::Modifier *modifier = factory->makeModifier();
                FilterModel::instance().addModifier(modifier);
                FilterModel::instance().setModifierState(modifier, !filterElem.hasAttribute("state") || filterElem.attribute("state").toInt());
                bool exclusive = filterElem.attribute("exclusive").toInt();
                if (exclusive)
                    FilterModel::instance().setExclusiveModifier(modifier);

                // Properties
                QDomElement propElem = filterElem.firstChildElement("properties").firstChildElement("property");
                QMap<QString,QPair<QString,QVariant> > properties;
                while (!propElem.isNull()) {
                    QString name = propElem.attribute("name");
                    QString type = propElem.attribute("type");
                    QVariant value(propElem.attribute("value"));

                    properties.insert(name, QPair<QString,QVariant>(type, value));

                    // To the next prop
                    propElem = propElem.nextSiblingElement("property");
                }
                modifier->deserializeProperties(properties);

                // Extension policy
                QDomElement extensionPolicyElem = filterElem.firstChildElement("extension_policy");
                if (!extensionPolicyElem.isNull()) {
                    FilterModel::instance().setLocalExtensionPolicyEnabled(static_cast<core::Filter*>(modifier), true);
                    FilterModel::instance().setLocalExtensionPolicy(static_cast<core::Filter*>(modifier), loadExtensionPolicy(extensionPolicyElem));
                }
            }

            // To the next modifier
            filterElem = filterElem.nextSiblingElement("modifier");
        }
    }
    return true;
}

bool Profile::save(const QString &fileName) {
    QDomDocument doc("renamah_profile");
    QFile file(fileName);

    doc.appendChild(doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'"));

    QDomElement rootElem = doc.createElement("profile");
    doc.appendChild(rootElem);

    // General extension policy
    saveExtensionPolicy(rootElem, FilterModel::instance().extensionPolicy());

    // Filters
    QDomElement filtersElem = doc.createElement("filters");
    rootElem.appendChild(filtersElem);
    for (int row = 0; row < FilterModel::instance().rowCount(); ++row) {
        core::Modifier *modifier = FilterModel::instance().modifier(FilterModel::instance().index(row, 0));

        QDomElement filterElem = doc.createElement("modifier");
        filtersElem.appendChild(filterElem);
        filterElem.setAttribute("factory", modifier->factory()->info().name());
        filterElem.setAttribute("state", FilterModel::instance().modifierState(modifier) ? "1" : "0");
        if (FilterModel::instance().exclusiveModifier() == modifier)
            filterElem.setAttribute("exclusive", "1");

        // Properties
        QDomElement propsElem = doc.createElement("properties");
        filterElem.appendChild(propsElem);
        QMap<QString,QPair<QString,QVariant> > properties = modifier->serializeProperties();
        foreach (const QString &name, properties.keys()) {
            const QPair<QString,QVariant> &pair = properties[name];
            QDomElement propElem = doc.createElement("property");
            propsElem.appendChild(propElem);
            propElem.setAttribute("name", name);
            propElem.setAttribute("type", pair.first);
            propElem.setAttribute("value", pair.second.toString());
        }

        // Extension policy
        if (FilterModel::instance().isLocalExtensionPolicyEnabled(static_cast<core::Filter*>(modifier)))
            saveExtensionPolicy(filterElem, FilterModel::instance().localExtensionPolicy(static_cast<core::Filter*>(modifier)));
    }

    // Finalizers
    QDomElement finalizersElem = doc.createElement("finalizers");
    rootElem.appendChild(finalizersElem);
    for (int row = 0; row < FinalizerModel::instance().rowCount(); ++row) {
        core::Modifier *modifier = FinalizerModel::instance().modifier(FinalizerModel::instance().index(row, 0));
        QDomElement finalizerElem = doc.createElement("modifier");
        finalizersElem.appendChild(finalizerElem);
    }

    if (file.open(QFile::WriteOnly)) {
        QTextStream stream(&file);
        stream << doc.toString(2);
    }
    return true;
}

void Profile::saveExtensionPolicy(QDomElement &root, const ExtensionPolicy &policy) {
    QDomDocument doc = root.ownerDocument();
    QDomElement policyElem = doc.createElement("extension_policy");
    root.appendChild(policyElem);

    QDomElement filterPolicyElem = doc.createElement("filter_policy");
    policyElem.appendChild(filterPolicyElem);
    QDomText t = doc.createTextNode(QString::number((int) policy.filterPolicy()));
    filterPolicyElem.appendChild(t);

    QDomElement extensionDefinitionElem = doc.createElement("extension_definition");
    policyElem.appendChild(extensionDefinitionElem);
    t = doc.createTextNode(QString::number((int) policy.extensionDefinition()));
    extensionDefinitionElem.appendChild(t);

    QDomElement nthPointFromRightElem = doc.createElement("nth_point_from_right");
    policyElem.appendChild(nthPointFromRightElem);
    t = doc.createTextNode(QString::number(policy.nthPointFromRight()));
    nthPointFromRightElem.appendChild(t);
}

ExtensionPolicy Profile::loadExtensionPolicy(const QDomElement &policyElem) {
    ExtensionPolicy policy;

    QDomElement filterPolicyElem = policyElem.firstChildElement("filter_policy");
    if (!filterPolicyElem.isNull())
        policy.setFilterPolicy((ExtensionPolicy::FilterPolicy) filterPolicyElem.text().toInt());

    QDomElement extensionDefinitionElem = policyElem.firstChildElement("extension_definition");
    if (!extensionDefinitionElem.isNull())
        policy.setExtensionDefinition((ExtensionPolicy::ExtensionDefinition) extensionDefinitionElem.text().toInt());

    QDomElement nthPointFromRightElem = policyElem.firstChildElement("nth_point_from_right");
    if (!nthPointFromRightElem.isNull())
        policy.setNthPointFromRight(nthPointFromRightElem.text().toInt());

    return policy;
}
