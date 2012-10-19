
LOCAL_PATH := $(call my-dir)
REAL_LOCAL_PATH := $(LOCAL_PATH)

RELATIVE_PATH := ../$(MY_TESSLIB_PATH)


include $(CLEAR_VARS)

LOCAL_MODULE := libtess

# scrollview_lib

LOCAL_SRC_FILES := \
  $(RELATIVE_PATH)/viewer/scrollview.cpp \
  $(RELATIVE_PATH)/viewer/svutil.cpp \
  $(RELATIVE_PATH)/viewer/svmnode.cpp \
  $(RELATIVE_PATH)/viewer/svpaint.cpp


LOCAL_CFLAGS := \
  -DHAVE_LIBLEPT

# tesseract_ccutil

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/ccutil/ambigs.cpp \
  $(RELATIVE_PATH)/ccutil/basedir.cpp \
  $(RELATIVE_PATH)/ccutil/bits16.cpp \
  $(RELATIVE_PATH)/ccutil/boxread.cpp \
  $(RELATIVE_PATH)/ccutil/clst.cpp \
  $(RELATIVE_PATH)/ccutil/debugwin.cpp \
  $(RELATIVE_PATH)/ccutil/elst.cpp \
  $(RELATIVE_PATH)/ccutil/elst2.cpp \
  $(RELATIVE_PATH)/ccutil/errcode.cpp \
  $(RELATIVE_PATH)/ccutil/globaloc.cpp \
  $(RELATIVE_PATH)/ccutil/hashfn.cpp \
  $(RELATIVE_PATH)/ccutil/mainblk.cpp \
  $(RELATIVE_PATH)/ccutil/memblk.cpp \
  $(RELATIVE_PATH)/ccutil/memry.cpp \
  $(RELATIVE_PATH)/ccutil/mfcpch.cpp \
  $(RELATIVE_PATH)/ccutil/ocrshell.cpp \
  $(RELATIVE_PATH)/ccutil/scanutils.cpp \
  $(RELATIVE_PATH)/ccutil/serialis.cpp \
  $(RELATIVE_PATH)/ccutil/strngs.cpp \
  $(RELATIVE_PATH)/ccutil/tessdatamanager.cpp \
  $(RELATIVE_PATH)/ccutil/tessopt.cpp \
  $(RELATIVE_PATH)/ccutil/tordvars.cpp \
  $(RELATIVE_PATH)/ccutil/tprintf.cpp \
  $(RELATIVE_PATH)/ccutil/unichar.cpp \
  $(RELATIVE_PATH)/ccutil/unicharset.cpp \
  $(RELATIVE_PATH)/ccutil/unicharmap.cpp \
  $(RELATIVE_PATH)/ccutil/varable.cpp \
  $(RELATIVE_PATH)/ccutil/ccutil.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/ccutil

# tesseract_cutil

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/cutil/tessarray.cpp \
  $(RELATIVE_PATH)/cutil/bitvec.cpp \
  $(RELATIVE_PATH)/cutil/danerror.cpp \
  $(RELATIVE_PATH)/cutil/efio.cpp \
  $(RELATIVE_PATH)/cutil/emalloc.cpp \
  $(RELATIVE_PATH)/cutil/freelist.cpp \
  $(RELATIVE_PATH)/cutil/globals.cpp \
  $(RELATIVE_PATH)/cutil/listio.cpp \
  $(RELATIVE_PATH)/cutil/oldheap.cpp \
  $(RELATIVE_PATH)/cutil/oldlist.cpp \
  $(RELATIVE_PATH)/cutil/structures.cpp \
  $(RELATIVE_PATH)/cutil/cutil.cpp \
  $(RELATIVE_PATH)/cutil/cutil_class.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/cutil \
  $(TESSERACT_PATH)/ccutil \

# tesseract_dict

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/dict/choices.cpp \
  $(RELATIVE_PATH)/dict/context.cpp \
  $(RELATIVE_PATH)/dict/conversion.cpp \
  $(RELATIVE_PATH)/dict/dawg.cpp \
  $(RELATIVE_PATH)/dict/dict.cpp \
  $(RELATIVE_PATH)/dict/hyphen.cpp \
  $(RELATIVE_PATH)/dict/permdawg.cpp \
  $(RELATIVE_PATH)/dict/permngram.cpp \
  $(RELATIVE_PATH)/dict/permute.cpp \
  $(RELATIVE_PATH)/dict/states.cpp \
  $(RELATIVE_PATH)/dict/stopper.cpp \
  $(RELATIVE_PATH)/dict/trie.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/cutil \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/ccstruct \
  $(TESSERACT_PATH)/dict \

# tesseract_image

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/image/image.cpp \
  $(RELATIVE_PATH)/image/imgbmp.cpp \
  $(RELATIVE_PATH)/image/imgio.cpp \
  $(RELATIVE_PATH)/image/imgs.cpp \
  $(RELATIVE_PATH)/image/imgtiff.cpp \
  $(RELATIVE_PATH)/image/bitstrm.cpp \
  $(RELATIVE_PATH)/image/svshowim.cpp
  
LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/image \
  $(TESSERACT_PATH)/viewer \
  $(LEPTONICA_PATH)/src

LOCAL_CFLAGS += \
  -DHAVE_LIBLEPT

# tesseract_cc_struct

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/ccstruct/blobbox.cpp \
  $(RELATIVE_PATH)/ccstruct/blobs.cpp \
  $(RELATIVE_PATH)/ccstruct/blread.cpp \
  $(RELATIVE_PATH)/ccstruct/callcpp.cpp \
  $(RELATIVE_PATH)/ccstruct/ccstruct.cpp \
  $(RELATIVE_PATH)/ccstruct/coutln.cpp \
  $(RELATIVE_PATH)/ccstruct/detlinefit.cpp \
  $(RELATIVE_PATH)/ccstruct/genblob.cpp \
  $(RELATIVE_PATH)/ccstruct/labls.cpp \
  $(RELATIVE_PATH)/ccstruct/linlsq.cpp \
  $(RELATIVE_PATH)/ccstruct/lmedsq.cpp \
  $(RELATIVE_PATH)/ccstruct/mod128.cpp \
  $(RELATIVE_PATH)/ccstruct/normalis.cpp \
  $(RELATIVE_PATH)/ccstruct/ocrblock.cpp \
  $(RELATIVE_PATH)/ccstruct/ocrrow.cpp \
  $(RELATIVE_PATH)/ccstruct/otsuthr.cpp \
  $(RELATIVE_PATH)/ccstruct/pageres.cpp \
  $(RELATIVE_PATH)/ccstruct/pdblock.cpp \
  $(RELATIVE_PATH)/ccstruct/points.cpp \
  $(RELATIVE_PATH)/ccstruct/polyaprx.cpp \
  $(RELATIVE_PATH)/ccstruct/polyblk.cpp \
  $(RELATIVE_PATH)/ccstruct/polyblob.cpp \
  $(RELATIVE_PATH)/ccstruct/polyvert.cpp \
  $(RELATIVE_PATH)/ccstruct/poutline.cpp \
  $(RELATIVE_PATH)/ccstruct/quadlsq.cpp \
  $(RELATIVE_PATH)/ccstruct/quadratc.cpp \
  $(RELATIVE_PATH)/ccstruct/quspline.cpp \
  $(RELATIVE_PATH)/ccstruct/ratngs.cpp \
  $(RELATIVE_PATH)/ccstruct/rect.cpp \
  $(RELATIVE_PATH)/ccstruct/rejctmap.cpp \
  $(RELATIVE_PATH)/ccstruct/statistc.cpp \
  $(RELATIVE_PATH)/ccstruct/stepblob.cpp \
  $(RELATIVE_PATH)/ccstruct/vecfuncs.cpp \
  $(RELATIVE_PATH)/ccstruct/werd.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/api \
  $(TESSERACT_PATH)/ccstruct \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/cutil \
  $(TESSERACT_PATH)/image \
  $(TESSERACT_PATH)/viewer \
  $(LEPTONICA_PATH)/src

# tesseract_classify

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/classify/adaptive.cpp \
  $(RELATIVE_PATH)/classify/adaptmatch.cpp \
  $(RELATIVE_PATH)/classify/baseline.cpp \
  $(RELATIVE_PATH)/classify/blobclass.cpp \
  $(RELATIVE_PATH)/classify/chartoname.cpp \
  $(RELATIVE_PATH)/classify/classify.cpp \
  $(RELATIVE_PATH)/classify/cluster.cpp \
  $(RELATIVE_PATH)/classify/clusttool.cpp \
  $(RELATIVE_PATH)/classify/cutoffs.cpp \
  $(RELATIVE_PATH)/classify/extract.cpp \
  $(RELATIVE_PATH)/classify/featdefs.cpp \
  $(RELATIVE_PATH)/classify/flexfx.cpp \
  $(RELATIVE_PATH)/classify/float2int.cpp \
  $(RELATIVE_PATH)/classify/fpoint.cpp \
  $(RELATIVE_PATH)/classify/fxdefs.cpp \
  $(RELATIVE_PATH)/classify/intfx.cpp \
  $(RELATIVE_PATH)/classify/intmatcher.cpp \
  $(RELATIVE_PATH)/classify/intproto.cpp \
  $(RELATIVE_PATH)/classify/kdtree.cpp \
  $(RELATIVE_PATH)/classify/mf.cpp \
  $(RELATIVE_PATH)/classify/mfdefs.cpp \
  $(RELATIVE_PATH)/classify/mfoutline.cpp \
  $(RELATIVE_PATH)/classify/mfx.cpp \
  $(RELATIVE_PATH)/classify/normfeat.cpp \
  $(RELATIVE_PATH)/classify/normmatch.cpp \
  $(RELATIVE_PATH)/classify/ocrfeatures.cpp \
  $(RELATIVE_PATH)/classify/outfeat.cpp \
  $(RELATIVE_PATH)/classify/picofeat.cpp \
  $(RELATIVE_PATH)/classify/protos.cpp \
  $(RELATIVE_PATH)/classify/speckle.cpp \
  $(RELATIVE_PATH)/classify/xform2d.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/cutil \
  $(TESSERACT_PATH)/classify \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/ccstruct \
  $(TESSERACT_PATH)/dict

# tesseract_textord

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/textord/alignedblob.cpp \
  $(RELATIVE_PATH)/textord/blkocc.cpp \
  $(RELATIVE_PATH)/textord/bbgrid.cpp \
  $(RELATIVE_PATH)/textord/colfind.cpp \
  $(RELATIVE_PATH)/textord/colpartition.cpp \
  $(RELATIVE_PATH)/textord/colpartitionset.cpp \
  $(RELATIVE_PATH)/textord/drawedg.cpp \
  $(RELATIVE_PATH)/textord/drawtord.cpp \
  $(RELATIVE_PATH)/textord/edgblob.cpp \
  $(RELATIVE_PATH)/textord/edgloop.cpp \
  $(RELATIVE_PATH)/textord/fpchop.cpp \
  $(RELATIVE_PATH)/textord/gap_map.cpp \
  $(RELATIVE_PATH)/textord/imagefind.cpp \
  $(RELATIVE_PATH)/textord/linefind.cpp \
  $(RELATIVE_PATH)/textord/makerow.cpp \
  $(RELATIVE_PATH)/textord/oldbasel.cpp \
  $(RELATIVE_PATH)/textord/pagesegmain.cpp \
  $(RELATIVE_PATH)/textord/pithsync.cpp \
  $(RELATIVE_PATH)/textord/pitsync1.cpp \
  $(RELATIVE_PATH)/textord/scanedg.cpp \
  $(RELATIVE_PATH)/textord/sortflts.cpp \
  $(RELATIVE_PATH)/textord/strokewidth.cpp \
  $(RELATIVE_PATH)/textord/tabfind.cpp \
  $(RELATIVE_PATH)/textord/tablefind.cpp \
  $(RELATIVE_PATH)/textord/tabvector.cpp \
  $(RELATIVE_PATH)/textord/topitch.cpp \
  $(RELATIVE_PATH)/textord/tordmain.cpp \
  $(RELATIVE_PATH)/textord/tospace.cpp \
  $(RELATIVE_PATH)/textord/tovars.cpp \
  $(RELATIVE_PATH)/textord/underlin.cpp \
  $(RELATIVE_PATH)/textord/wordseg.cpp \
  $(RELATIVE_PATH)/textord/workingpartset.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/ccstruct \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/image \
  $(TESSERACT_PATH)/viewer \
  $(TESSERACT_PATH)/textord

LOCAL_CFLAGS += \
  -DHAVE_LIBLEPT

# tesseract_wordrec

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/wordrec/associate.cpp \
  $(RELATIVE_PATH)/wordrec/badwords.cpp \
  $(RELATIVE_PATH)/wordrec/bestfirst.cpp \
  $(RELATIVE_PATH)/wordrec/chop.cpp \
  $(RELATIVE_PATH)/wordrec/chopper.cpp \
  $(RELATIVE_PATH)/wordrec/closed.cpp \
  $(RELATIVE_PATH)/wordrec/drawfx.cpp \
  $(RELATIVE_PATH)/wordrec/findseam.cpp \
  $(RELATIVE_PATH)/wordrec/gradechop.cpp \
  $(RELATIVE_PATH)/wordrec/heuristic.cpp \
  $(RELATIVE_PATH)/wordrec/makechop.cpp \
  $(RELATIVE_PATH)/wordrec/matchtab.cpp \
  $(RELATIVE_PATH)/wordrec/matrix.cpp \
  $(RELATIVE_PATH)/wordrec/metrics.cpp \
  $(RELATIVE_PATH)/wordrec/mfvars.cpp \
  $(RELATIVE_PATH)/wordrec/olutil.cpp \
  $(RELATIVE_PATH)/wordrec/outlines.cpp \
  $(RELATIVE_PATH)/wordrec/pieces.cpp \
  $(RELATIVE_PATH)/wordrec/plotedges.cpp \
  $(RELATIVE_PATH)/wordrec/plotseg.cpp \
  $(RELATIVE_PATH)/wordrec/render.cpp \
  $(RELATIVE_PATH)/wordrec/seam.cpp \
  $(RELATIVE_PATH)/wordrec/split.cpp \
  $(RELATIVE_PATH)/wordrec/tally.cpp \
  $(RELATIVE_PATH)/wordrec/tessinit.cpp \
  $(RELATIVE_PATH)/wordrec/tface.cpp \
  $(RELATIVE_PATH)/wordrec/wordclass.cpp \
  $(RELATIVE_PATH)/wordrec/wordrec.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/ccstruct \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/cutil \
  $(TESSERACT_PATH)/cstruct \
  $(TESSERACT_PATH)/classify \
  $(TESSERACT_PATH)/image \
  $(TESSERACT_PATH)/dict \
  $(TESSERACT_PATH)/viewer

# tesseract_main

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/ccmain/tessedit.cpp \
  $(RELATIVE_PATH)/ccmain/adaptions.cpp \
  $(RELATIVE_PATH)/ccmain/ambigsrecog.cpp \
  $(RELATIVE_PATH)/ccmain/applybox.cpp \
  $(RELATIVE_PATH)/ccmain/blobcmp.cpp \
  $(RELATIVE_PATH)/ccmain/callnet.cpp \
  $(RELATIVE_PATH)/ccmain/charcut.cpp \
  $(RELATIVE_PATH)/ccmain/charsample.cpp \
  $(RELATIVE_PATH)/ccmain/control.cpp \
  $(RELATIVE_PATH)/ccmain/docqual.cpp \
  $(RELATIVE_PATH)/ccmain/expandblob.cpp \
  $(RELATIVE_PATH)/ccmain/fixspace.cpp \
  $(RELATIVE_PATH)/ccmain/fixxht.cpp \
  $(RELATIVE_PATH)/ccmain/imgscale.cpp \
  $(RELATIVE_PATH)/ccmain/matmatch.cpp \
  $(RELATIVE_PATH)/ccmain/osdetect.cpp \
  $(RELATIVE_PATH)/ccmain/output.cpp \
  $(RELATIVE_PATH)/ccmain/pagewalk.cpp \
  $(RELATIVE_PATH)/ccmain/paircmp.cpp \
  $(RELATIVE_PATH)/ccmain/pgedit.cpp \
  $(RELATIVE_PATH)/ccmain/reject.cpp \
  $(RELATIVE_PATH)/ccmain/scaleimg.cpp \
  $(RELATIVE_PATH)/ccmain/tessbox.cpp \
  $(RELATIVE_PATH)/ccmain/tesseractclass.cpp \
  $(RELATIVE_PATH)/ccmain/tessvars.cpp \
  $(RELATIVE_PATH)/ccmain/tfacepp.cpp \
  $(RELATIVE_PATH)/ccmain/thresholder.cpp \
  $(RELATIVE_PATH)/ccmain/tstruct.cpp \
  $(RELATIVE_PATH)/ccmain/varabled.cpp \
  $(RELATIVE_PATH)/ccmain/werdit.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/ccstruct \
  $(TESSERACT_PATH)/image \
  $(TESSERACT_PATH)/viewer \
  $(TESSERACT_PATH)/dict \
  $(TESSERACT_PATH)/classify \
  $(TESSERACT_PATH)/wordrec \
  $(TESSERACT_PATH)/cutil \
  $(TESSERACT_PATH)/textord \
  $(TESSERACT_PATH)/ccmain \
  $(LEPTONICA_PATH)/src

LOCAL_CFLAGS += \
  -DHAVE_LIBLEPT

# tesseract_api

LOCAL_SRC_FILES += \
  $(RELATIVE_PATH)/api/baseapi.cpp

LOCAL_C_INCLUDES += \
  $(TESSERACT_PATH)/api \
  $(TESSERACT_PATH)/ccutil \
  $(TESSERACT_PATH)/ccstruct \
  $(TESSERACT_PATH)/image \
  $(TESSERACT_PATH)/viewer \
  $(TESSERACT_PATH)/dict \
  $(TESSERACT_PATH)/classify \
  $(TESSERACT_PATH)/wordrec \
  $(TESSERACT_PATH)/cutil \
  $(TESSERACT_PATH)/textord \
  $(TESSERACT_PATH)/ccmain \
  $(LEPTONICA_PATH)/src

LOCAL_CFLAGS += \
  -DHAVE_LIBLEPT

# jni

LOCAL_SRC_FILES += \
tessbaseapi.cpp

LOCAL_C_INCLUDES += \
  $(REAL_LOCAL_PATH) \
  $(TESSERACT_PATH)/api \
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

LOCAL_PRELINK_MODULE := false
LOCAL_SHARED_LIBRARIES := liblept




include $(BUILD_SHARED_LIBRARY)
