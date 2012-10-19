/*************

Singleton class for processing and recognizing characters in an image.

*************/


#ifndef _IMAGEPROCESSOR_H
#define _IMAGEPROCESSOR_H


#include "baseapi.h"


typedef unsigned char pixel;


class ImageProcessor{

public:

	
	// Initializes the processor for images with the specified width and height, and whether to rotate
	// the image 90 degrees.
	// tessDir should be the absolute data path of tessdata, tessLang should be the language or null for eng.
	// Returns 0 if successful, -1 otherwise
	int Initialize(int width, int height, bool rotate, const char* tessDir, const char* tessLang);


	// Sets the image source data to the specified byte array of image data stored in NV21 format.
	void SetSourceData(signed char *bytes);


	// Processes the image to prepare it for character recognition. Must be called after SetSourceData().
	void ProcessImage();


	// Returns the recognized text from the image. Must be called after ProcessImage().
	const char *GetText() const;


	// Gets the current array of pixel colors.
	int* GetPixelColors() { return mPixelColors; }


	// Returns the number of pixels in the image.
	const int GetPixelCount() const { return mPixelCount; }


	// Returns the width of the current image.
	const int GetWidth() const { return mWidth; }


	// Returns the height of the current image.
	const int GetHeight() const { return mHeight; }


	// Gets the current instance of the image processor
	static ImageProcessor *GetInstance();

	~ImageProcessor();


	bool _ISFILTERING;

private:

	ImageProcessor();
	ImageProcessor(const ImageProcessor&);
	ImageProcessor& operator=(const ImageProcessor&);


	tesseract::TessBaseAPI mTessApi;


	inline int ClipRGB(int in);


	void BinarizeImage();


	void AvgBinarization();
	void ExtremesBinarization();



	static ImageProcessor *mInstance;


	bool mRotate;

	int mWidth;
	int mHeight;

	int mPixelCount;

	int mGlobalColorAverage;


	int mGlobalHighColor;
	int mGlobalLowColor;
	int mGlobalMedColor;


	int *mPixelColors;


	pixel *mGrayPixels;

	bool mIsImageOld;

	char *mText;

};


#endif // _IMAGEPROCESSOR_H