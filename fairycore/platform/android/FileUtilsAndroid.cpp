#include "stdafx.h"
#include <stdio.h>
#include <android/log.h>
#include "platform/android/fairycore_android.h"

static AAssetManager* g_aassetManager = 0;

void setupAssetManager(JNIEnv* env, jobject assetManager)
{
	g_aassetManager = AAssetManager_fromJava(env, assetManager);
}

FileUtils::FileData FileUtils::getFileData(const char* fileName)
{
	DebugLog::print( "FileUtils::getFileData(%s)", fileName );

	AAsset* asset = AAssetManager_open(g_aassetManager, (const char *) fileName, AASSET_MODE_UNKNOWN);
    if (NULL == asset) {
        DebugLog::print("Failed !");
        return FileData();
    }

    long size = AAsset_getLength(asset);
    FileData res = findFreeFileDataSlot(size);	
    res.size = size;
    
    AAsset_read (asset, res.bytes, size);
    AAsset_close(asset);	

    return res;
}

