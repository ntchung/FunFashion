LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := FunFashion
LOCAL_SRC_FILES := FunFashion.cpp

LOCAL_LDLIBS := \
    -llog -lGLESv2

LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../fairycore $(LOCAL_PATH)/../../../fashiongame

LOCAL_WHOLE_STATIC_LIBRARIES := fashiongame_static fairycore_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, ../..)
$(call import-module,fashiongame)
$(call import-module,fairycore)
