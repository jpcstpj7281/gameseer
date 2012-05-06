LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -lm -llog
LOCAL_MODULE    := test
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include/
LOCAL_C_INCLUDES += $(HAXEPATH)/lib/hxcpp/2,08,0/include/
LOCAL_SRC_FILES := ../../common/ExternalInterface.cpp 

include $(BUILD_SHARED_LIBRARY)

