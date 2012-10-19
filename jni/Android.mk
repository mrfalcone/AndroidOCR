
PROFILER_ENABLED := false

LOCAL_PATH := $(call my-dir)
REAL_LOCAL_PATH := $(LOCAL_PATH)

MY_TESSERACT_PATH := $(LOCAL_PATH)/tesseract


MY_TESSLIB_PATH := tesseract-3.00
MY_LEPTLIB_PATH := leptonlib-1.66
MY_JPEGLIB_PATH := libjpeg

TESSERACT_PATH := $(MY_TESSERACT_PATH)/$(MY_TESSLIB_PATH)
LEPTONICA_PATH := $(MY_TESSERACT_PATH)/$(MY_LEPTLIB_PATH)
LIBJPEG_PATH := $(MY_TESSERACT_PATH)/$(MY_JPEGLIB_PATH)



# include libandprof
ifeq ($(PROFILER_ENABLED),true) 

	TARGET_thumb_release_CFLAGS := $(filter-out -ffunction-sections,$(TARGET_thumb_release_CFLAGS))
	TARGET_thumb_release_CFLAGS := $(filter-out -fomit-frame-pointer,$(TARGET_thumb_release_CFLAGS))
	TARGET_CFLAGS := $(filter-out -ffunction-sections,$(TARGET_CFLAGS))

	
	LOCAL_PATH := $(MY_TESSERACT_PATH)
	
	include $(CLEAR_VARS)

	LOCAL_MODULE := andprof
	LOCAL_SRC_FILES := libandprof.a
	
	include $(PREBUILT_STATIC_LIBRARY)

	
	LOCAL_PATH := $(REAL_LOCAL_PATH)

endif



include $(CLEAR_VARS)


LOCAL_MODULE    := AndroidOCR
LOCAL_SRC_FILES := AndroidOCR.cpp \
ImageProcessor.cpp





ifeq ($(PROFILER_ENABLED),true) 

	LOCAL_CPPFLAGS += \
	  -DPROFILING_ENABLED
	  
	LOCAL_LDLIBS := -llog
	  
	LOCAL_C_INCLUDES += $(MY_TESSERACT_PATH)
	
	LOCAL_LDFLAGS := -pg

	LOCAL_CFLAGS := -pg
	LOCAL_STATIC_LIBRARIES := andprof

endif


LOCAL_SHARED_LIBRARIES := tess

include $(BUILD_SHARED_LIBRARY)

include $(MY_TESSERACT_PATH)/lept/Android.mk
include $(MY_TESSERACT_PATH)/tess/Android.mk
include $(LIBJPEG_PATH)/Android.mk
