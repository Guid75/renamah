#ifndef FILTER_FILE_INFO_H
#define FILTER_FILE_INFO_H

class QString;

namespace core
{
	class FilterFileInfo
	{
	public:
		FilterFileInfo(const QString &originalFilePath,
					   const QString &partToFilter,
					   int fileIndex) {
			this->originalFilePath = originalFilePath;
			this->partToFilter = partToFilter;
			this->fileIndex = fileIndex;
		}

		QString originalFilePath; //!< the complete original file path
		QString partToFilter; //!< the file part to filter
		int fileIndex; //!< the index of the file in all files to filter
	};
};

#endif
