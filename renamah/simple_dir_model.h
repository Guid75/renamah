#ifndef SIMPLE_DIR_MODEL_H
#define SIMPLE_DIR_MODEL_H

#include <QDirModel>

class SimpleDirModel : public QDirModel
{
     Q_OBJECT
public:
     int columnCount(const QModelIndex & parent = QModelIndex()) const;
};

#endif
