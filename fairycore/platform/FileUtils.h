#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

#include "utils/SharedObject.h"
#include "utils/DynamicArray.h"

class FileUtils : public SharedObject
{
public:
	struct FileData
	{
		char* bytes;
		int size;
		int capacity;
	};

	static FileUtils* shared();
	virtual void destroy();

	FileData& getFileData(const char* fileName);
	void recycleFileData(FileData& data);

private:
	FileUtils();
	~FileUtils();	

	DynamicArray<FileData, 8> m_listFileData;
	FileData& findFreeFileDataSlot(int size);
};

#endif // __FILEUTILS_H__
