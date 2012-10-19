/*
 * Copyright 2010, Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "common.h"
#include "string.h"

#ifdef IS_FRAMEWORK
#include <core/SkBitmap.h>
#else 
#ifdef HAS_JNIGRAPHICS
#include "android/bitmap.h"
#endif /* HAS_JNIGRPAHICS */
#endif /* IS_FRAMEWORK */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/***************
 * AdaptiveMap *
 ***************/

jint Java_com_googlecode_leptonica_android_AdaptiveMap_nativeBackgroundNormMorph(JNIEnv *env,
                                                                                 jclass clazz,
                                                                                 jint nativePix,
                                                                                 jint reduction,
                                                                                 jint size,
                                                                                 jint bgval) {
  LOGV(__FUNCTION__);
  // Normalizes the background of each element in pixa.

  PIX *pixs = (PIX *) nativePix;
  PIX *pixd = pixBackgroundNormMorph(pixs, NULL, (l_int32) reduction, (l_int32) size,
                                     (l_int32) bgval);

  return (jint) pixd;
}

/************
 * Binarize *
 ************/

jint Java_com_googlecode_leptonica_android_Binarize_nativeOtsuAdaptiveThreshold(JNIEnv *env,
                                                                                jclass clazz,
                                                                                jint nativePix,
                                                                                jint sizeX,
                                                                                jint sizeY,
                                                                                jint smoothX,
                                                                                jint smoothY,
                                                                                jfloat scoreFract) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;
  PIX *pixd;

  if (pixOtsuAdaptiveThreshold(pixs, (l_int32) sizeX, (l_int32) sizeY, (l_int32) smoothX,
                               (l_int32) smoothY, (l_float32) scoreFract, NULL, &pixd)) {
    return (jint) 0;
  }

  return (jint) pixd;
}

/***********
 * Convert *
 ***********/

jint Java_com_googlecode_leptonica_android_Convert_nativeConvertTo8(JNIEnv *env, jclass clazz,
                                                                    jint nativePix) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;
  PIX *pixd = pixConvertTo8(pixs, FALSE);

  return (jint) pixd;
}

/***********
 * Enhance *
 ***********/

jint Java_com_googlecode_leptonica_android_Enhance_nativeUnsharpMasking(JNIEnv *env, jclass clazz,
                                                                        jint nativePix,
                                                                        jint halfwidth,
                                                                        jfloat fract) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;
  PIX *pixd = pixUnsharpMasking(pixs, (l_int32) halfwidth, (l_float32) fract);

  return (jint) pixd;
}

/**********
 * JpegIO *
 **********/

jbyteArray Java_com_googlecode_leptonica_android_JpegIO_nativeCompressToJpeg(JNIEnv *env,
                                                                             jclass clazz,
                                                                             jint nativePix,
                                                                             jint quality,
                                                                             jboolean progressive) {
  LOGV(__FUNCTION__);

  PIX *pix = (PIX *) nativePix;

  l_uint8 *data;
  size_t size;

  if (pixWriteMemJpeg(&data, &size, pix, (l_int32) quality, progressive == JNI_TRUE ? 1 : 0)) {
    LOGE("Failed to write JPEG data");

    return NULL;
  }

  // TODO Can we just use the byte array directly?
  jbyteArray array = env->NewByteArray(size);
  env->SetByteArrayRegion(array, 0, size, (jbyte *) data);

  free(data);

  return array;
}

/************
 * ReadFile *
 ************/

jint Java_com_googlecode_leptonica_android_ReadFile_nativeReadMem(JNIEnv *env, jclass clazz,
                                                                  jbyteArray image, jint length) {
  LOGV(__FUNCTION__);

  jbyte *image_buffer = env->GetByteArrayElements(image, NULL);
  int buffer_length = env->GetArrayLength(image);

  PIX *pix = pixReadMem((const l_uint8 *) image_buffer, buffer_length);

  env->ReleaseByteArrayElements(image, image_buffer, JNI_ABORT);

  return (jint) pix;
}

jint Java_com_googlecode_leptonica_android_ReadFile_nativeReadBytes8(JNIEnv *env, jclass clazz,
                                                                     jbyteArray data, jint w,
                                                                     jint h) {
  LOGV(__FUNCTION__);

  PIX *pix = pixCreateNoInit((l_int32) w, (l_int32) h, 8);
  l_uint8 **lineptrs = pixSetupByteProcessing(pix, NULL, NULL);
  jbyte *data_buffer = env->GetByteArrayElements(data, NULL);
  l_uint8 *byte_buffer = (l_uint8 *) data_buffer;

  for (int i = 0; i < h; i++) {
    memcpy(lineptrs[i], (byte_buffer + (i * w)), w);
  }

  env->ReleaseByteArrayElements(data, data_buffer, JNI_ABORT);
  pixCleanupByteProcessing(pix, lineptrs);

  l_int32 d;

  pixGetDimensions(pix, &w, &h, &d);

  LOGE("Created image width w=%d, h=%d, d=%d", w, h, d);

  return (jint) pix;
}

jboolean Java_com_googlecode_leptonica_android_ReadFile_nativeReplaceBytes8(JNIEnv *env,
                                                                            jclass clazz,
                                                                            jint nativePix,
                                                                            jbyteArray data,
                                                                            jint srcw, jint srch) {
  LOGV(__FUNCTION__);

  PIX *pix = (PIX *) nativePix;
  l_int32 w, h, d;

  pixGetDimensions(pix, &w, &h, &d);

  if (d != 8 || (l_int32) srcw != w || (l_int32) srch != h) {
    LOGE("Failed to replace bytes at w=%d, h=%d, d=%d with w=%d, h=%d", w, h, d, srcw, srch);

    return JNI_FALSE;
  }

  l_uint8 **lineptrs = pixSetupByteProcessing(pix, NULL, NULL);
  jbyte *data_buffer = env->GetByteArrayElements(data, NULL);
  l_uint8 *byte_buffer = (l_uint8 *) data_buffer;

  for (int i = 0; i < h; i++) {
    memcpy(lineptrs[i], (byte_buffer + (i * w)), w);
  }

  env->ReleaseByteArrayElements(data, data_buffer, JNI_ABORT);
  pixCleanupByteProcessing(pix, lineptrs);

  return JNI_TRUE;
}

jint Java_com_googlecode_leptonica_android_ReadFile_nativeReadFiles(JNIEnv *env, jclass clazz,
                                                                    jstring dirName, jstring prefix) {
  LOGV(__FUNCTION__);

  PIXA *pixad = NULL;

  const char *c_dirName = env->GetStringUTFChars(dirName, NULL);
  if (c_dirName == NULL) {
    LOGE("could not extract dirName string!");
    return NULL;
  }

  const char *c_prefix = env->GetStringUTFChars(prefix, NULL);
  if (c_prefix == NULL) {
    LOGE("could not extract prefix string!");
    return NULL;
  }

  pixad = pixaReadFiles(c_dirName, c_prefix);

  env->ReleaseStringUTFChars(dirName, c_dirName);
  env->ReleaseStringUTFChars(prefix, c_prefix);

  return (jint) pixad;
}

jint Java_com_googlecode_leptonica_android_ReadFile_nativeReadFile(JNIEnv *env, jclass clazz,
                                                                   jstring fileName) {
  LOGV(__FUNCTION__);

  PIX *pixd = NULL;

  const char *c_fileName = env->GetStringUTFChars(fileName, NULL);
  if (c_fileName == NULL) {
    LOGE("could not extract fileName string!");
    return NULL;
  }

  pixd = pixRead(c_fileName);

  env->ReleaseStringUTFChars(fileName, c_fileName);

  return (jint) pixd;
}

#ifdef HAS_JNIGRAPHICS
jint Java_com_googlecode_leptonica_android_ReadFile_nativeReadBitmap(JNIEnv *env,
    jclass clazz,
    jobject bitmap) {
  LOGV(__FUNCTION__);

  l_int32 w, h, d;
  AndroidBitmapInfo info;
  void* pixels;
  int ret;

  if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
    LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
    return JNI_FALSE;
  }

  if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
    LOGE("Bitmap format is not RGBA_8888 !");
    return JNI_FALSE;
  }

  if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
    LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    return JNI_FALSE;
  }

  PIX *pix = pixCreate(info.width, info.height, 8);

  l_uint8 *src = (l_uint8 *) pixels;
  l_uint8 *dst = (l_uint8 *) pixGetData(pixs);
  l_int32 srcBpl = info.stride;
  l_int32 dstBpl = 4 * pixGetWpl(pixs);
  l_uint8 a, r, g, b;

  SET_PIXEL = SET_PIXEL_8;

  for (int y = 0; y < info.height; y++) {
    l_uint8 *dst_line = dst + (y * dstBpl);
    l_uint8 *src_line = src + (y * srcBpl);

    for (int x = 0; x < info.width; x++) {
      // Get pixel from ARGB_8888
      r = *src_line++;
      g = *src_line++;
      b = *src_line++;
      a = *src_line++;

      // Set pixel to LUMA_8
      *dst_line = (l_uint8) ((r + g + b) / 3);
    }
  }

  AndroidBitmap_unlockPixels(env, bitmap);

  return (jint) pix;
}
#else
jint Java_com_googlecode_leptonica_android_ReadFile_nativeReadBitmap(JNIEnv *env,
    jclass clazz,
    jint nativePix,
    jobject bitmap) {
  LOGV(__FUNCTION__);

  LOGE("Bitmap format is not supported");

  return JNI_FALSE;
}
#endif /* HAS_JNIGRAPHICS */

/*********
 * Scale *
 *********/

jint Java_com_googlecode_leptonica_android_Scale_nativeScale(JNIEnv *env, jclass clazz,
                                                             jint nativePix, jfloat scaleX,
                                                             jfloat scaleY) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;
  PIX *pixd = pixScale(pixs, (l_float32) scaleX, (l_float32) scaleY);

  return (jint) pixd;
}

/********
 * Skew *
 ********/

jfloat Java_com_googlecode_leptonica_android_Skew_nativeFindSkew(JNIEnv *env, jclass clazz,
                                                                 jint nativePix, jfloat sweepRange,
                                                                 jfloat sweepDelta,
                                                                 jint sweepReduction,
                                                                 jint searchReduction,
                                                                 jfloat searchMinDelta) {
  LOGV(__FUNCTION__);
  // Corrects the rotation of each element in pixa to 0 degrees.

  PIX *pixs = (PIX *) nativePix;

  l_float32 angle, conf;

  if (!pixFindSkewSweepAndSearch(pixs, &angle, &conf, (l_int32) sweepReduction,
                                 (l_int32) searchReduction, (l_float32) sweepRange,
                                 (l_int32) sweepDelta, (l_float32) searchMinDelta)) {
    if (conf <= 0) {
      return (jfloat) 0;
    }

    return (jfloat) angle;
  }

  return (jfloat) 0;
}

/**********
 * Rotate *
 **********/

jint Java_com_googlecode_leptonica_android_Rotate_nativeRotate(JNIEnv *env, jclass clazz,
                                                               jint nativePix, jfloat degrees,
                                                               jboolean quality) {
  LOGV(__FUNCTION__);

  PIX *pixd;
  PIX *pixs = (PIX *) nativePix;

  l_float32 deg2rad = 3.1415926535 / 180.0;
  l_float32 radians = degrees * deg2rad;
  l_int32 w, h, bpp, type;

  pixGetDimensions(pixs, &w, &h, &bpp);

  if (bpp == 1 && quality == JNI_TRUE) {
    pixd = pixRotateBinaryNice(pixs, radians, L_BRING_IN_WHITE);
  } else {
    type = quality == JNI_TRUE ? L_ROTATE_AREA_MAP : L_ROTATE_SAMPLING;
    pixd = pixRotate(pixs, radians, type, L_BRING_IN_WHITE, 0, 0);
  }

  return (jint) pixd;
}

/*************
 * WriteFile *
 *************/

jint Java_com_googlecode_leptonica_android_WriteFile_nativeWriteBytes8(JNIEnv *env, jclass clazz,
                                                                       jint nativePix,
                                                                       jbyteArray data) {
  LOGV(__FUNCTION__);

  l_int32 w, h, d;
  PIX *pix = (PIX *) nativePix;
  pixGetDimensions(pix, &w, &h, &d);

  l_uint8 **lineptrs = pixSetupByteProcessing(pix, NULL, NULL);
  jbyte *data_buffer = env->GetByteArrayElements(data, NULL);
  l_uint8 *byte_buffer = (l_uint8 *) data_buffer;

  for (int i = 0; i < h; i++) {
    memcpy((byte_buffer + (i * w)), lineptrs[i], w);
  }

  env->ReleaseByteArrayElements(data, data_buffer, 0);
  pixCleanupByteProcessing(pix, lineptrs);

  return (jint) (w * h);
}

jboolean Java_com_googlecode_leptonica_android_WriteFile_nativeWriteFiles(JNIEnv *env,
                                                                          jclass clazz,
                                                                          jint nativePixa,
                                                                          jstring rootName,
                                                                          jint format) {
  LOGV(__FUNCTION__);

  PIXA *pixas = (PIXA *) nativePixa;

  const char *c_rootName = env->GetStringUTFChars(rootName, NULL);
  if (c_rootName == NULL) {
    LOGE("could not extract rootName string!");
    return JNI_FALSE;
  }

  jboolean result = JNI_TRUE;

  if (pixaWriteFiles(c_rootName, pixas, (l_uint32) format)) {
    LOGE("could not write pixa data to %s", c_rootName);
    result = JNI_FALSE;
  }

  env->ReleaseStringUTFChars(rootName, c_rootName);

  return result;
}

jbyteArray Java_com_googlecode_leptonica_android_WriteFile_nativeWriteMem(JNIEnv *env,
                                                                          jclass clazz,
                                                                          jint nativePix,
                                                                          jint format) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;

  l_uint8 *data;
  size_t size;

  if (pixWriteMem(&data, &size, pixs, (l_uint32) format)) {
    LOGE("Failed to write pix data");
    return NULL;
  }

  // TODO Can we just use the byte array directly?
  jbyteArray array = env->NewByteArray(size);
  env->SetByteArrayRegion(array, 0, size, (jbyte *) data);

  free(data);

  return array;
}

jboolean Java_com_googlecode_leptonica_android_WriteFile_nativeWriteImpliedFormat(
                                                                                  JNIEnv *env,
                                                                                  jclass clazz,
                                                                                  jint nativePix,
                                                                                  jstring fileName,
                                                                                  jint quality,
                                                                                  jboolean progressive) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;

  const char *c_fileName = env->GetStringUTFChars(fileName, NULL);
  if (c_fileName == NULL) {
    LOGE("could not extract fileName string!");
    return JNI_FALSE;
  }

  jboolean result = JNI_TRUE;

  if (pixWriteImpliedFormat(c_fileName, pixs, (l_int32) quality, (progressive == JNI_TRUE))) {
    LOGE("could not write pix data to %s", c_fileName);
    result = JNI_FALSE;
  }

  env->ReleaseStringUTFChars(fileName, c_fileName);

  return result;
}

#ifdef HAS_JNIGRAPHICS
jboolean Java_com_googlecode_leptonica_android_WriteFile_nativeWriteBitmap(JNIEnv *env,
    jclass clazz,
    jint nativePix,
    jobject bitmap) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;

  l_int32 w, h, d;
  AndroidBitmapInfo info;
  void* pixels;
  int ret;

  if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
    LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
    return JNI_FALSE;
  }

  if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
    LOGE("Bitmap format is not RGBA_8888 !");
    return JNI_FALSE;
  }

  pixGetDimensions(pixs, &w, &h, &d);

  if (w != info.width || h != info.height) {
    LOGE("Bitmap width and height do not match Pix dimensions!");
    return JNI_FALSE;
  }

  if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
    LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    return JNI_FALSE;
  }

  pixEndianByteSwap(pixs);

  l_uint8 *dst = (l_uint8 *) pixels;
  l_uint8 *src = (l_uint8 *) pixGetData(pixs);
  l_int32 dstBpl = info.stride;
  l_int32 srcBpl = 4 * pixGetWpl(pixs);

  LOGE("Writing 32bpp RGBA bitmap (w=%d, h=%d, stride=%d) from %dbpp Pix (wpl=%d)", info.width,
      info.height, info.stride, d, pixGetWpl(pixs));

  for (int dy = 0; dy < info.height; dy++) {
    l_uint8 *dstx = dst;
    l_uint8 *srcx = src;

    if (d == 32) {
      memcpy(dst, src, 4 * info.width);
    } else if (d == 8) {
      for (int dw = 0; dw < info.width; dw++) {
        dstx[0] = dstx[1] = dstx[2] = srcx[0];
        dstx[3] = 0xFF;

        dstx += 4;
        srcx += 1;
      }
    } else if (d == 1) {
      for (int dw = 0; dw < info.width; dw++) {
        dstx[0] = dstx[1] = dstx[2] = (srcx[0] & (dw % 8)) ? 0xFF : 0x00;
        dstx[3] = 0xFF;

        dstx += 4;
        srcx += ((dw % 8) == 7) ? 1 : 0;
      }
    }

    dst += dstBpl;
    src += srcBpl;
  }

  AndroidBitmap_unlockPixels(env, bitmap);

  return JNI_TRUE;
}
#else
jboolean Java_com_googlecode_leptonica_android_WriteFile_nativeWriteBitmap(JNIEnv *env,
    jclass clazz,
    jint nativePix,
    jobject bitmap) {
  LOGV(__FUNCTION__);

  LOGE("Bitmap format is not supported");

  return JNI_FALSE;
}
#endif /* HAS_JNIGRAPHICS */

#ifdef __cplusplus
}
#endif  /* __cplusplus */
