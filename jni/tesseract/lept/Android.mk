LOCAL_PATH := $(call my-dir)
REAL_LOCAL_PATH := $(LOCAL_PATH)

RELATIVE_PATH := ../$(MY_LEPTLIB_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE := liblept

# leptonica (minus freetype)

#BLACKLIST_SRC_FILES := \
#  %endiantest.c \
#  %freetype.c \
#  %xtractprotos.c

#LOCAL_SRC_FILES := \
#  $(filter-out $(BLACKLIST_SRC_FILES),$(wildcard $(RELATIVE_PATH)/src/*.c))

LOCAL_SRC_FILES := \
$(RELATIVE_PATH)/src/adaptmap.c \
$(RELATIVE_PATH)/src/affine.c \
$(RELATIVE_PATH)/src/affinecompose.c \
$(RELATIVE_PATH)/src/arithlow.c \
$(RELATIVE_PATH)/src/arrayaccess.c \
$(RELATIVE_PATH)/src/bardecode.c \
$(RELATIVE_PATH)/src/baseline.c \
$(RELATIVE_PATH)/src/bbuffer.c \
$(RELATIVE_PATH)/src/bilinear.c \
$(RELATIVE_PATH)/src/binarize.c \
$(RELATIVE_PATH)/src/binexpand.c \
$(RELATIVE_PATH)/src/binexpandlow.c \
$(RELATIVE_PATH)/src/binreduce.c \
$(RELATIVE_PATH)/src/binreducelow.c \
$(RELATIVE_PATH)/src/blend.c \
$(RELATIVE_PATH)/src/bmf.c \
$(RELATIVE_PATH)/src/bmpio.c \
$(RELATIVE_PATH)/src/bmpiostub.c \
$(RELATIVE_PATH)/src/boxbasic.c \
$(RELATIVE_PATH)/src/boxfunc1.c \
$(RELATIVE_PATH)/src/boxfunc2.c \
$(RELATIVE_PATH)/src/boxfunc3.c \
$(RELATIVE_PATH)/src/ccbord.c \
$(RELATIVE_PATH)/src/ccthin.c \
$(RELATIVE_PATH)/src/classapp.c \
$(RELATIVE_PATH)/src/colorcontent.c \
$(RELATIVE_PATH)/src/colormap.c \
$(RELATIVE_PATH)/src/colormorph.c \
$(RELATIVE_PATH)/src/colorquant1.c \
$(RELATIVE_PATH)/src/colorquant2.c \
$(RELATIVE_PATH)/src/colorseg.c \
$(RELATIVE_PATH)/src/compare.c \
$(RELATIVE_PATH)/src/conncomp.c \
$(RELATIVE_PATH)/src/convolve.c \
$(RELATIVE_PATH)/src/convolvelow.c \
$(RELATIVE_PATH)/src/correlscore.c \
$(RELATIVE_PATH)/src/dewarp.c \
$(RELATIVE_PATH)/src/dwacomb.2.c \
$(RELATIVE_PATH)/src/dwacomblow.2.c \
$(RELATIVE_PATH)/src/edge.c \
$(RELATIVE_PATH)/src/enhance.c \
$(RELATIVE_PATH)/src/fhmtauto.c \
$(RELATIVE_PATH)/src/fhmtgen.1.c \
$(RELATIVE_PATH)/src/fhmtgenlow.1.c \
$(RELATIVE_PATH)/src/finditalic.c \
$(RELATIVE_PATH)/src/flipdetect.c \
$(RELATIVE_PATH)/src/fliphmtgen.c \
$(RELATIVE_PATH)/src/fmorphauto.c \
$(RELATIVE_PATH)/src/fmorphgen.1.c \
$(RELATIVE_PATH)/src/fmorphgenlow.1.c \
$(RELATIVE_PATH)/src/fpix1.c \
$(RELATIVE_PATH)/src/fpix2.c \
$(RELATIVE_PATH)/src/gifio.c \
$(RELATIVE_PATH)/src/gifiostub.c \
$(RELATIVE_PATH)/src/gplot.c \
$(RELATIVE_PATH)/src/graphics.c \
$(RELATIVE_PATH)/src/graymorph.c \
$(RELATIVE_PATH)/src/graymorphlow.c \
$(RELATIVE_PATH)/src/grayquant.c \
$(RELATIVE_PATH)/src/grayquantlow.c \
$(RELATIVE_PATH)/src/heap.c \
$(RELATIVE_PATH)/src/jbclass.c \
$(RELATIVE_PATH)/src/jpegio.c \
$(RELATIVE_PATH)/src/jpegiostub.c \
$(RELATIVE_PATH)/src/kernel.c \
$(RELATIVE_PATH)/src/leptwin.c \
$(RELATIVE_PATH)/src/list.c \
$(RELATIVE_PATH)/src/maze.c \
$(RELATIVE_PATH)/src/morph.c \
$(RELATIVE_PATH)/src/morphapp.c \
$(RELATIVE_PATH)/src/morphdwa.c \
$(RELATIVE_PATH)/src/morphseq.c \
$(RELATIVE_PATH)/src/numabasic.c \
$(RELATIVE_PATH)/src/numafunc1.c \
$(RELATIVE_PATH)/src/numafunc2.c \
$(RELATIVE_PATH)/src/pageseg.c \
$(RELATIVE_PATH)/src/paintcmap.c \
$(RELATIVE_PATH)/src/parseprotos.c \
$(RELATIVE_PATH)/src/partition.c \
$(RELATIVE_PATH)/src/pix1.c \
$(RELATIVE_PATH)/src/pix2.c \
$(RELATIVE_PATH)/src/pix3.c \
$(RELATIVE_PATH)/src/pix4.c \
$(RELATIVE_PATH)/src/pix5.c \
$(RELATIVE_PATH)/src/pixabasic.c \
$(RELATIVE_PATH)/src/pixacc.c \
$(RELATIVE_PATH)/src/pixafunc1.c \
$(RELATIVE_PATH)/src/pixafunc2.c \
$(RELATIVE_PATH)/src/pixalloc.c \
$(RELATIVE_PATH)/src/pixarith.c \
$(RELATIVE_PATH)/src/pixcomp.c \
$(RELATIVE_PATH)/src/pixconv.c \
$(RELATIVE_PATH)/src/pixtiling.c \
$(RELATIVE_PATH)/src/pngio.c \
$(RELATIVE_PATH)/src/pngiostub.c \
$(RELATIVE_PATH)/src/pnmio.c \
$(RELATIVE_PATH)/src/pnmiostub.c \
$(RELATIVE_PATH)/src/projective.c \
$(RELATIVE_PATH)/src/psio1.c \
$(RELATIVE_PATH)/src/psio1stub.c \
$(RELATIVE_PATH)/src/psio2.c \
$(RELATIVE_PATH)/src/psio2stub.c \
$(RELATIVE_PATH)/src/ptabasic.c \
$(RELATIVE_PATH)/src/ptafunc1.c \
$(RELATIVE_PATH)/src/ptra.c \
$(RELATIVE_PATH)/src/queue.c \
$(RELATIVE_PATH)/src/rank.c \
$(RELATIVE_PATH)/src/readbarcode.c \
$(RELATIVE_PATH)/src/readfile.c \
$(RELATIVE_PATH)/src/regutils.c \
$(RELATIVE_PATH)/src/rop.c \
$(RELATIVE_PATH)/src/ropiplow.c \
$(RELATIVE_PATH)/src/roplow.c \
$(RELATIVE_PATH)/src/rotate.c \
$(RELATIVE_PATH)/src/rotateam.c \
$(RELATIVE_PATH)/src/rotateamlow.c \
$(RELATIVE_PATH)/src/rotateorth.c \
$(RELATIVE_PATH)/src/rotateorthlow.c \
$(RELATIVE_PATH)/src/rotateshear.c \
$(RELATIVE_PATH)/src/runlength.c \
$(RELATIVE_PATH)/src/sarray.c \
$(RELATIVE_PATH)/src/scale.c \
$(RELATIVE_PATH)/src/scalelow.c \
$(RELATIVE_PATH)/src/seedfill.c \
$(RELATIVE_PATH)/src/seedfilllow.c \
$(RELATIVE_PATH)/src/sel1.c \
$(RELATIVE_PATH)/src/sel2.c \
$(RELATIVE_PATH)/src/selgen.c \
$(RELATIVE_PATH)/src/shear.c \
$(RELATIVE_PATH)/src/skew.c \
$(RELATIVE_PATH)/src/spixio.c \
$(RELATIVE_PATH)/src/stack.c \
$(RELATIVE_PATH)/src/textops.c \
$(RELATIVE_PATH)/src/tiffio.c \
$(RELATIVE_PATH)/src/tiffiostub.c \
$(RELATIVE_PATH)/src/utils.c \
$(RELATIVE_PATH)/src/viewfiles.c \
$(RELATIVE_PATH)/src/warper.c \
$(RELATIVE_PATH)/src/watershed.c \
$(RELATIVE_PATH)/src/writefile.c \
$(RELATIVE_PATH)/src/zlibmem.c \
$(RELATIVE_PATH)/src/zlibmemstub.c



LOCAL_CFLAGS := \
  -DHAVE_CONFIG_H

LOCAL_C_INCLUDES := \
  $(LIBJPEG_PATH)

LOCAL_LDLIBS := \
  -lz

# missing stdio functions

ifneq ($(TARGET_SIMULATOR),true)
LOCAL_SRC_FILES += \
stdio/open_memstream.c \
stdio/fopencookie.c \
stdio/fmemopen.c
LOCAL_C_INCLUDES += \
  $(REAL_LOCAL_PATH)/stdio
endif

# jni

LOCAL_SRC_FILES += \
box.cpp \
pix.cpp \
pixa.cpp \
utilities.cpp \
jni.cpp
 
LOCAL_C_INCLUDES += \
  $(REAL_LOCAL_PATH) \
  $(LEPTONICA_PATH)/src

LOCAL_LDLIBS += \
  -llog

# support for native bitmap

LOCAL_CPPFLAGS += \
  -DHAVE_JNIGRAPHICS
LOCAL_LDLIBS += \
  -ljnigraphics

# common

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SHARED_LIBRARIES:= libjpeg
LOCAL_PRELINK_MODULE:= false


include $(BUILD_SHARED_LIBRARY)
