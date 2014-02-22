#include "stdafx.h"

FileUtils* g_sharedFileUtils = 0;

FileUtils* FileUtils::shared()
{
	if (!g_sharedFileUtils)
	{
		g_sharedFileUtils = new FileUtils();
		g_sharedFileUtils->autorelease();
		g_sharedFileUtils->retain();
	}

	return g_sharedFileUtils;
}

void FileUtils::destroy()
{
	delete this;
}

FileUtils::FileUtils()
{

}

FileUtils::~FileUtils()
{
	for (int i = 0; i < m_listFileData.count(); ++i)
	{
		delete[] m_listFileData[i].bytes;
	}
}

void FileUtils::recycleFileData(FileData& data)
{
	m_listFileData.add(data);
}

FileUtils::FileData FileUtils::findFreeFileDataSlot(int size)
{
	FileData res;

	int i;
	int k = -1;

	for (i = 0; i < m_listFileData.count(); ++i)
	{
		if (m_listFileData[i].capacity >= size)
		{
			k = i;
			break;
		}
	}

	for (i = k+1; i < m_listFileData.count(); ++i)
	{
		if (m_listFileData[i].capacity >= size && 
			m_listFileData[i].capacity < m_listFileData[k].capacity)
		{
			k = i;
		}
	}
			
	if (k >= 0)
	{
		res = m_listFileData[k];
		m_listFileData.removeAt(k);
		return res;
	}

	res.bytes = new char[size];
	res.size = 0;
	res.capacity = size;
	return res;
}
