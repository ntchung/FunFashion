LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := fairycore_static

LOCAL_MODULE_FILENAME := libfairycore

LOCAL_SRC_FILES := \
platform/FileUtils.cpp \
platform/android/DebugLog.cpp \
platform/android/FileUtilsAndroid.cpp \
Resources.cpp \
Camera.cpp \
Shader.cpp \
FairyCore.cpp \
FairyHeart.cpp \
Transform.cpp \
utils/MemoryStream.cpp \
utils/MemoryPool.cpp \
utils/ObjectsPool.cpp \
utils/SharedObject.cpp \
utils/String.cpp \
utils/StreamReader.cpp \
gui/GUI.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_LDLIBS := -lGLESv2 \
                -llog \
                -lz

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz

include $(BUILD_STATIC_LIBRARY)
