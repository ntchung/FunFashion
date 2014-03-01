LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE := fashiongame_static

LOCAL_MODULE_FILENAME := libfashiongame

LOCAL_SRC_FILES := \
FashionGame.cpp \
TestRenderer.cpp \
StateTest.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/../fairycore

LOCAL_EXPORT_LDLIBS := -lGLESv2 \
                       -llog \
                       -lz

include $(BUILD_STATIC_LIBRARY)
