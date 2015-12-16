LOCAL_PATH := $(call my-dir)  
include $(CLEAR_VARS) 
LOCAL_SRC_FILES := Pinyin.c \
                   Array.c \
                   SearchCore.c
LOCAL_MODULE := libpinyin
LOCAL_CFLAGS += -std=c99  
include $(BUILD_SHARED_LIBRARY)  