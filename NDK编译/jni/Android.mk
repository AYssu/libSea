# LOCAL_PATH := $(call my-dir)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := Sea
LOCAL_SRC_FILES := include/libSea.a
include $(PREBUILT_STATIC_LIBRARY)
 
include $(CLEAR_VARS)
LOCAL_SRC_FILES := Empty.cpp
LOCAL_STATIC_LIBRARIES := Sea
LOCAL_MODULE := Empty
# LOCAL_CPPFLAGS += -mllvm -sub -mllvm -fla -mllvm -split -mllvm -sobf -mllvm -aesSeed=0x345678EDCRFVTGBYHNUJMIKOLPloveal
LOCAL_LDFLAGS += -llog -landroid
include $(BUILD_EXECUTABLE)

