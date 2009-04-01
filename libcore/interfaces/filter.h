#ifndef FILTER_H
#define FILTER_H

class QString;

#include "modifier.h"
#include "filter_file_info.h"

namespace core
{
	class Filter : public Modifier
	{
		Q_OBJECT

	public:
		Filter(QObject *parent = 0) : Modifier(parent) {}

		/*! Returns the filtered string of the parameter partToFilter which is a part of the parameter filePath
		 * \param partToFilter The filename part to filter
		 * \param filePath the complete file path
		 */
		virtual QString apply(const FilterFileInfo &fileInfo) const = 0;
	};
};

#endif
