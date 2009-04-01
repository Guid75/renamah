#ifndef MODIFIER_MODEL_H
#define MODIFIER_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include <interfaces/filter.h>

class ModifierModel : public QAbstractListModel
{
	Q_OBJECT

public:
	static const int colIndex = 3;
	static const int colMode = 0;
	static const int colCaption = 1;
	static const int columnNumber = 2;

	ModifierModel();

	/*! Returns a modifier in function of a model index */
	core::Modifier *modifier(const QModelIndex &index) const;

	/*! Add a modifier to the model */
	void addModifier(core::Modifier *modifier);

	/*! Remove the modifier at <index> */
	void removeModifier(const QModelIndex &index);

	/*! Clear all modifiers */
	virtual void clear();

	/*! Returns the modifier state */
	bool modifierState(core::Modifier *modifier) const;

	/*! Activate or deactivate a modifier */
	void setModifierState(core::Modifier *modifier, bool state);

	/*! Toggle the state of the modifier */
	void toggleModifierState(core::Modifier *modifier);

	/*! Set a modifier as the uniq modifier, deactivate others */
	void setExclusiveModifier(core::Modifier *modifier);

	/*! If modifier was not exclusive => set it exclusive */
	void toggleExclusiveState(core::Modifier *modifier);

	/*! Up the modifier which index is in parameter
	 * \returns true if the operation has been succeed
	 */
	bool upModifier(const QModelIndex &modifierIndex);

	/*! Down the modifier which index is in parameter
	 * \returns true if the operation has been succeed
	 */
	bool downModifier(const QModelIndex &modifierIndex);

	/*! Returns the exclusive modifier */
	core::Modifier *exclusiveModifier() const { return _exclusiveModifier; }

	void refreshLayout() { emit layoutChanged(); }

	int dropRow() const { return _dropRow; }

	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	Qt::DropActions supportedDropActions() const;
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

signals:
	void modifiersChanged();
	void dropDone();

protected:
	QList<core::Modifier*> _modifiers;
	QMap<core::Modifier*, bool> _modifierStates;
	core::Modifier *_exclusiveModifier;

private:
	int _dropRow;
};

#endif
