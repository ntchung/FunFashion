#include "stdafx.h"
#include <stdio.h>

FileUtils::FileData& FileUtils::getFileData(const char* fileName)
{
	char fullPath[_MAX_PATH];
	memset(fullPath, 0, _MAX_PATH);
	strcpy(fullPath, "data\\");
	strcat(fullPath, fileName);

	FILE *fp = fopen(fullPath, "rb");

	int size;
	fseek(fp, 0, SEEK_END);
	size = (int)ftell(fp);
	fseek(fp, 0, SEEK_SET);

	FileData res = findFreeFileDataSlot(size);			
	size = fread(res.bytes, sizeof(unsigned char), size, fp);
	fclose(fp);

	return res;
}

