LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := FunFashion
LOCAL_SRC_FILES := FunFashion.cpp

LOCAL_LDLIBS := \
    -llog -lGLESv2

LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)
