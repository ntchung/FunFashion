#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "platform/FileUtils.h"
#include "utils/SharedObject.h"

class List;

class Resources : public SharedObject
{
public:
	static Resources* shared();

	template <class T> T* load(const char* filename)
	{
		T* obj = (T*)findInCache(filename);
		if (!obj)
		{
			FileUtils::FileData fileData = FileUtils::shared()->getFileData(filename);
			obj = T::create(fileData.bytes, fileData.size);
			FileUtils::shared()->recycleFileData(fileData);

			m_cachedObjects->add(obj);
		}

		return obj;
	}

private:
	Resources();
	~Resources();

	virtual void destroy();

	SharedObject* findInCache(const char* name);

	List* m_cachedObjects;
};

#endif // __RESOURCES_H__
