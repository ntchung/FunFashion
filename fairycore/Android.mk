LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE := fairycore_static

LOCAL_MODULE_FILENAME := libfairycore

LOCAL_SRC_FILES := \
platform/FileUtils.cpp \
platform/android/DebugLog.cpp \
platform/android/FileUtilsAndroid.cpp \
Resources.cpp \
Shader.cpp \
Material.cpp \
RenderBatch.cpp \
Camera.cpp \
FairyCore.cpp \
FairyHeart.cpp \
Transform.cpp \
utils/PVRTPFXSemantics.cpp \
utils/MemoryStream.cpp \
utils/MemoryPool.cpp \
utils/ObjectsPool.cpp \
utils/SharedObject.cpp \
utils/List.cpp \
utils/ByteArray.cpp \
utils/RecyclingMemory.cpp \
utils/String.cpp \
utils/StreamReader.cpp \
utils/UIDGenerator.cpp \
maths/Mathf.cpp \
gui/GUI.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz

include $(BUILD_STATIC_LIBRARY)
