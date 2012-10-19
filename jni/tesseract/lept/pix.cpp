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
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

jint Java_com_googlecode_leptonica_android_Pix_nativeCreateFromData(JNIEnv *env, jclass clazz,
                                                                     jbyteArray data, jint w,
                                                                     jint h, jint d) {
  LOGV(__FUNCTION__);

  PIX *pix = pixCreateNoInit((l_int32) w, (l_int32) h, (l_int32) d);

  jbyte *data_buffer = env->GetByteArrayElements(data, NULL);
  l_uint8 *byte_buffer = (l_uint8 *) data_buffer;

  size_t size = 4 * pixGetWpl(pix) * pixGetHeight(pix);
  memcpy(pixGetData(pix), byte_buffer, size);

  env->ReleaseByteArrayElements(data, data_buffer, JNI_ABORT);

  return (jint) pix;
}

jboolean Java_com_googlecode_leptonica_android_Pix_nativeGetData(JNIEnv *env, jclass clazz,
                                                                  jint nativePix, jbyteArray data) {
  LOGV(__FUNCTION__);

  PIX *pix = (PIX *) nativePix;

  jbyte *data_buffer = env->GetByteArrayElements(data, NULL);
  l_uint8 *byte_buffer = (l_uint8 *) data_buffer;

  size_t size = 4 * pixGetWpl(pix) * pixGetHeight(pix);
  memcpy(byte_buffer, pixGetData(pix), size);

  env->ReleaseByteArrayElements(data, data_buffer, 0);

  return JNI_TRUE;
}

jint Java_com_googlecode_leptonica_android_Pix_nativeGetDataSize(JNIEnv *env, jclass clazz,
                                                                  jint nativePix) {
  LOGV(__FUNCTION__);

  PIX *pix = (PIX *) nativePix;

  size_t size = 4 * pixGetWpl(pix) * pixGetHeight(pix);

  return (jint) size;
}

jint Java_com_googlecode_leptonica_android_Pix_nativeClone(JNIEnv *env, jclass clazz,
                                                           jint nativePix) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;
  PIX *pixd = pixClone(pixs);

  return (jint) pixd;
}

jint Java_com_googlecode_leptonica_android_Pix_nativeCopy(JNIEnv *env, jclass clazz,
                                                           jint nativePix) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;
  PIX *pixd = pixCopy(NULL, pixs);

  return (jint) pixd;
}

jboolean Java_com_googlecode_leptonica_android_Pix_nativeInvert(JNIEnv *env, jclass clazz,
                                                                 jint nativePix) {
  LOGV(__FUNCTION__);

  PIX *pixs = (PIX *) nativePix;

  if (pixInvert(pixs, pixs)) {
    return JNI_FALSE;
  }

  return JNI_TRUE;
}

void Java_com_googlecode_leptonica_android_Pix_nativeDestroy(JNIEnv *env, jclass clazz,
                                                              jint nativePix) {
  LOGV(__FUNCTION__);

  PIX *pix = (PIX *) nativePix;

  pixDestroy(&pix);
}

jboolean Java_com_googlecode_leptonica_android_Pix_nativeGetDimensions(JNIEnv *env, jclass clazz,
                                                                        jint nativePix,
                                                                        jintArray dimensions) {
  LOGV(__FUNCTION__);

  PIX *pix = (PIX *) nativePix;
  jint *dimensionArray = env->GetIntArrayElements(dimensions, NULL);
  l_int32 w, h, d;

  if (pixGetDimensions(pix, &w, &h, &d)) {
    return JNI_FALSE;
  }

  dimensionArray[0] = w;
  dimensionArray[1] = h;
  dimensionArray[2] = d;

  env->ReleaseIntArrayElements(dimensions, dimensionArray, 0);

  return JNI_TRUE;
}

jint Java_com_googlecode_leptonica_android_Pix_nativeGetWidth(JNIEnv *env, jclass clazz,
                                                               jint nativePix) {
  PIX *pix = (PIX *) nativePix;

  return (jint) pixGetWidth(pix);
}

jint Java_com_googlecode_leptonica_android_Pix_nativeGetHeight(JNIEnv *env, jclass clazz,
                                                                jint nativePix) {
  PIX *pix = (PIX *) nativePix;

  return (jint) pixGetHeight(pix);
}

jint Java_com_googlecode_leptonica_android_Pix_nativeGetDepth(JNIEnv *env, jclass clazz,
                                                               jint nativePix) {
  PIX *pix = (PIX *) nativePix;

  return (jint) pixGetDepth(pix);
}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
