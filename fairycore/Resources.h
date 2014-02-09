#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "platform/FileUtils.h"
#include "utils/SharedObject.h"

class Resources : public SharedObject
{
public:
	static Resources* shared();

	template <class T> T* load(const char* filename)
	{
		FileUtils::FileData fileData = FileUtils::shared()->getFileData(filename);		
		T* obj = T::create(fileData.bytes);
		FileUtils::shared()->recycleFileData(fileData);
		return obj;
	}

private:
	Resources();
	~Resources();

	virtual void destroy();
};

#endif // __RESOURCES_H__
