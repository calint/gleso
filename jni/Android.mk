LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE:=libjni
LOCAL_CFLAGS:=-std=c++11 -Wall -Wextra -pedantic
LOCAL_SRC_FILES:=jni.cpp
LOCAL_LDLIBS:=-llog -lGLESv2
include $(BUILD_SHARED_LIBRARY)
LOCAL_CPP_FEATURES += exceptions