#ifndef EXTENSION_POLICY_H
#define EXTENSION_POLICY_H

#include <QDir>

#include <interfaces/filter.h>

class ExtensionPolicy
{
public:
    enum FilterPolicy {
        FilterBaseName,
        FilterExtension,
        FilterAll
    };

    enum ExtensionDefinition {
        FirstPoint,
        LastPoint,
        NthPointFromRight
    };

    ExtensionPolicy() :
            _filterPolicy(FilterBaseName),
            _extensionDefinition(LastPoint),
            _nthPointFromRight(1) {}

    FilterPolicy filterPolicy() const { return _filterPolicy; }
    void setFilterPolicy(FilterPolicy value) { _filterPolicy = value; }

    ExtensionDefinition extensionDefinition() const { return _extensionDefinition; }
    void setExtensionDefinition(ExtensionDefinition value) { _extensionDefinition = value; }

    int nthPointFromRight() const { return _nthPointFromRight; }
    void setNthPointFromRight(int value) { _nthPointFromRight = value; }

    bool operator==(const ExtensionPolicy &other) const {
        return _filterPolicy == other._filterPolicy &&
                _extensionDefinition == other._extensionDefinition &&
                _nthPointFromRight == other._nthPointFromRight;
    }

    QString applyFilterOnFilePath(const core::Filter &filter, int fileIndex, const QString &filePath, const QString &originalFilePath) const;

    /*! Reset to default settings */
    void reset();

private:
    FilterPolicy _filterPolicy;
    ExtensionDefinition _extensionDefinition;
    int _nthPointFromRight;

    void getBaseNameAndExtension(const QString &filePath, QString &baseName, QString &extension) const;
    QString getFilePath(const QString &baseName, const QString &extension, const QDir &dir) const;
};

#endif
