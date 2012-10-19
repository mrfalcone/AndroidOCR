/*
Main library source file.
*/

#include <jni.h>
#include <string.h>


#include "ImageProcessor.h"

#ifdef PROFILING_ENABLED
#include "prof.h"

#define PROF_LIBNAME "libAndroidOCR.so"

#endif




static ImageProcessor *ip = ImageProcessor::GetInstance();

static jmethodID setPixelsMethod; 


#ifdef __cplusplus
extern "C" {
#endif

/// native methods ///

JNIEXPORT jint JNICALL Java_com_ocr_OCRMain_initAndroidOCR(JNIEnv *env, jobject obj, jint width, jint height,
	jboolean rotate, jstring tessDir, jstring tessLang){

		const char* dir = env->GetStringUTFChars(tessDir, JNI_FALSE);
		const char* lang = env->GetStringUTFChars(tessLang, JNI_FALSE);
		
		if(ip->Initialize(width, height, (bool)rotate, dir, lang) < 0)
			return -1;

		env->ReleaseStringUTFChars(tessDir, dir);
		env->ReleaseStringUTFChars(tessLang, lang);



		jclass bitmapClass = env->FindClass("android/graphics/Bitmap");

		setPixelsMethod = env->GetMethodID(bitmapClass, "setPixels", "([IIIIIII)V");


		return 0;
}


JNIEXPORT void JNICALL Java_com_ocr_OCRMain_processBitmapOverlay(JNIEnv *env, jobject obj, jbyteArray bytes, jobject bitmap){



	// get the source bytes and send them to the image processor
	jbyte *nv21Data = env->GetByteArrayElements(bytes, JNI_FALSE);

	ip->SetSourceData(nv21Data);

	env->ReleaseByteArrayElements(bytes, nv21Data, 0);


	ip->ProcessImage();


	// get processed pixels and write them to the bitmap
	jintArray pixels = env->NewIntArray(ip->GetPixelCount());
	jint *buf = ip->GetPixelColors();


	env->SetIntArrayRegion(pixels, 0, ip->GetPixelCount(), buf);

	env->CallObjectMethod(bitmap, setPixelsMethod, pixels, 0, ip->GetWidth(), 0, 0, ip->GetWidth(), ip->GetHeight());

	env->ReleaseIntArrayElements(pixels, buf, 0);

}



JNIEXPORT jstring JNICALL Java_com_ocr_OCRMain_setIsFiltering(JNIEnv *env, jobject obj, jboolean filter){

	ip->_ISFILTERING = (bool)filter;

}



JNIEXPORT jstring JNICALL Java_com_ocr_OCRMain_getImageText(JNIEnv *env, jobject obj){


	jstring s = env->NewStringUTF(ip->GetText());

	return s;

}






JNIEXPORT void JNICALL Java_com_ocr_OCRMain_startProfile(JNIEnv *env, jobject obj){
#ifdef PROFILING_ENABLED
	monstartup(PROF_LIBNAME);
#endif
}

JNIEXPORT void JNICALL Java_com_ocr_OCRMain_endProfile(JNIEnv *env, jobject obj){
#ifdef PROFILING_ENABLED
	moncleanup();
#endif
}



#ifdef __cplusplus
}
#endif
