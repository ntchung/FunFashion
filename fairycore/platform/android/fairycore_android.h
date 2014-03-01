#ifndef __FAIRYCORE_ANDROID_H__
#define __FAIRYCORE_ANDROID_H__

#include <jni.h>
#include <android/asset_manager.h>
#include <android\asset_manager_jni.h>

void setupAssetManager(JNIEnv* env, jobject manager);

#endif // __FAIRYCORE_ANDROID_H__
