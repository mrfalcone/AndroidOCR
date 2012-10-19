#include <string.h>
#include <math.h>

#include "ImageProcessor.h"


ImageProcessor * ImageProcessor::mInstance = NULL;



ImageProcessor::ImageProcessor()
: mWidth(0), mHeight(0), mPixelCount(0), mPixelColors(NULL), mGrayPixels(NULL),
mRotate(false), mGlobalColorAverage(0), mGlobalHighColor(0), mGlobalLowColor(0),
mGlobalMedColor(0), mIsImageOld(true), mText(NULL){

	_ISFILTERING = true;

	//mTessApi = tesseract::TessBaseAPI();
}



ImageProcessor::~ImageProcessor(){

	if(mPixelColors != NULL){

		delete [] mPixelColors;
		mPixelColors = NULL;
	}

	if(mGrayPixels != NULL){

		delete [] mGrayPixels;
		mGrayPixels = NULL;
	}

	if(mText != NULL)
			delete [] mText;
}


ImageProcessor * ImageProcessor::GetInstance(){

	if(mInstance == NULL)
		mInstance = new ImageProcessor();

	return mInstance;
}


int ImageProcessor::Initialize(int width, int height, bool rotate, const char* tessDir, const char* tessLang){


	if(mTessApi.Init(tessDir, tessLang) < 0)
		return -1;


	mRotate = rotate;

	mWidth = width;
	mHeight = height;

	mPixelCount = width * height;


	// allocate a new array of pixel colors
	if(mPixelColors != NULL){

		delete [] mPixelColors;
		mPixelColors = NULL;
	}

	if(mGrayPixels != NULL){

		delete [] mGrayPixels;
		mGrayPixels = NULL;
	}

	mPixelColors = new int[mPixelCount];
	mGrayPixels = new pixel[mPixelCount];

	return 0;
}



const char * ImageProcessor::GetText() const{
	return mText;
}



void ImageProcessor::SetSourceData(signed char *bytes){

	if(!mIsImageOld)
		return;


	int curPixel = 0;

	int colorSum = 0;
	

	for(int row=0; row < mHeight; ++row){

		//int R,G,B = 0;
		//int U,V = 0;

		//int uvPlanePos = (row >> 1) * mWidth + mPixelCount;


		for(int col=0; col < mWidth; ++col,++curPixel){


			pixel luma = *(bytes+curPixel);


			if(luma < 1)
				luma = 1;


			if(row == 0 && col == 0){

				mGlobalHighColor = luma;
				mGlobalLowColor = luma;
			}



			//if(luma > 16)
			//	luma -= 16;
			//else
			//	luma = 0;


			

			if(!mRotate)

				*(mGrayPixels+curPixel) = luma;
			
			else{

				int destOffset = col * mWidth + (mHeight - row - 1);
				*(mGrayPixels+destOffset) = luma;
			}

			


			if (luma < mGlobalLowColor)
				mGlobalLowColor = luma;

			else if (luma > mGlobalHighColor)
				mGlobalHighColor = luma;
			
			
			colorSum += luma;


			/*int Y = (int)*(bytes+curPixel) & 0xFF;
			Y -= 16;*/
			

			// UV data spans 2 pixels, so get data every other pixel
			//if(!(col & 1)){

			//	V = (int)*(bytes+uvPlanePos) & 0xFF;
			//	++uvPlanePos;

			//	U = (int)*(bytes+uvPlanePos) & 0xFF;
			//	++uvPlanePos;

			//	V -= 128;
			//	U -= 128;
			//}
			

			// compute RGB values by Microsoft's method posted on MSDN
			//Y *= 298;
			//R = ClipRGB((Y           + 409 * V + 128) >> 8);
			//G = ClipRGB((Y - 100 * U - 208 * V + 128) >> 8);
			//B = ClipRGB((Y + 516 * U           + 128) >> 8);


			// convert to grayscale
			//Y = ClipRGB(Y);
			//int value = 0xFF000000 | (Y << 16) | (Y << 8) | Y;


			//int value = 0xFF000000 | (R << 16) | (G << 8) | B;


			//if(!mRotate)

			//	*(mCurrentPixels+curPixel) = value;
			//
			//else{

			//	int offset = col * mWidth + (mHeight - row - 1);
			//	*(mCurrentPixels+offset) = value;
			//}
			

		}


	}

	mGlobalMedColor = mGlobalHighColor - mGlobalLowColor;

	mGlobalColorAverage = (colorSum / mPixelCount) & 0xFF;
	
	
}


int ImageProcessor::ClipRGB(int in){

	if(in < 0)
		return 0;

	if(in > 255)
		return 255;

	return in;
}


void ImageProcessor::ProcessImage(){

	if(mIsImageOld){

		BinarizeImage();


		for(int i=0; i < mPixelCount; ++i){

			int value = *(mGrayPixels+i) & 0xFF;

			*(mPixelColors+i) = 0xFF000000 | (value << 16) | (value << 8) | value;
		}
		mIsImageOld = false;
	}

	else{

		if(mText != NULL)
			delete [] mText;

		mTessApi.SetImage(mGrayPixels, mWidth, mHeight, 1, mWidth);
		mText = mTessApi.GetUTF8Text();

		mIsImageOld = true;
	}

}




void ImageProcessor::BinarizeImage(){

	

	if(_ISFILTERING)
		ExtremesBinarization();
	else
		AvgBinarization();
}



void ImageProcessor::AvgBinarization(){


	pixel *temp = new pixel[mPixelCount];

	int neighbors[9];

	for(int col=1; col < mWidth-1; col+=3){

		for(int row=1; row < mHeight-1; row+=3){

			// get array offsets for all pixels in a 3x3 neighborhood surrounding the current pixel
			/*int topLeft = (row-1)*mWidth+col-1;
			int topCenter = topLeft+1;
			int topRight = topCenter+1;

			int leftCenter = row*mWidth+col-1;
			int curPixel = leftCenter+1;
			int rightCenter = curPixel+1;

			int bottomLeft = (row+1)*mWidth+col-1;
			int bottomCenter = bottomLeft+1;
			int bottomRight = bottomCenter+1;*/


			neighbors[0] = (row-1)*mWidth+col-1;
			neighbors[1] = neighbors[0]+1;
			neighbors[2] = neighbors[0]+2;

			neighbors[3] = row*mWidth+col-1;
			neighbors[4] = neighbors[3]+1;
			neighbors[5] = neighbors[3]+2;

			neighbors[6] = (row+1)*mWidth+col-1;
			neighbors[7] = neighbors[6]+1;
			neighbors[8] = neighbors[6]+2;


			for(int i=0; i < 9; ++i){

				int o = neighbors[i];


				float contrast = fabs( *(mGrayPixels+o) - mGlobalColorAverage) / mGlobalColorAverage;


				// if contrast with average is high then this is likely a foreground pixel
				if( contrast > 0.7f)
					*(temp+o) = 0;


				// otherwise we must check the pixel against the rest of the neighbors
				else{

					*(temp+o) = 255;



				}
			}
			


		}
	}


	// replace the current pixels
	pixel *oldPixels = mGrayPixels;
	mGrayPixels = temp;

	delete [] oldPixels;

}



void ImageProcessor::ExtremesBinarization(){


	pixel *temp = new pixel[mPixelCount];

	int neighbors[9];

	for(int col=1; col < mWidth-1; col+=3){

		for(int row=1; row < mHeight-1; row+=3){


			int localAvg = 0;

			int localHighColor = mGlobalColorAverage;
			int localLowColor = mGlobalColorAverage;



			neighbors[0] = (row-1)*mWidth+col-1;
			neighbors[1] = neighbors[0]+1;
			neighbors[2] = neighbors[0]+2;

			neighbors[3] = row*mWidth+col-1;
			neighbors[4] = neighbors[3]+1;
			neighbors[5] = neighbors[3]+2;

			neighbors[6] = (row+1)*mWidth+col-1;
			neighbors[7] = neighbors[6]+1;
			neighbors[8] = neighbors[6]+2;



			// compute the high, low, and average pixel colors in the neighborhood
			int colorSum = 0;
			for(int i=0; i < 9; ++i){

				int color = mGrayPixels[ neighbors[i] ] & 0xFF;

				if(color < localLowColor)
					localLowColor = color;
				else if(color > localHighColor)
					localHighColor = color;
				
				colorSum += color;
			}
			
			localAvg = colorSum / 9;



			// compute variation of the neighborhood average from global average, high color, low color, and middle color
			double variationAvg = fabs(localAvg - mGlobalColorAverage) / (double)mGlobalColorAverage ;
			double variationHigh = fabs(localAvg - mGlobalHighColor) / (double)mGlobalHighColor;
			double variationLow = fabs(localAvg - mGlobalLowColor) / (double)mGlobalLowColor;
			double variationMed = fabs(localAvg - mGlobalMedColor) / (double)mGlobalMedColor;


			// if neighborhood average color is close to extreme values of the image, pixels may be foreground
			if (variationHigh < variationAvg || variationLow < variationAvg || variationMed < variationAvg){

				for(int i=0; i < 9; ++i)
					temp[ neighbors[i] ] = 0;

			}


			else{

				for(int i=0; i < 9; ++i)
					temp[ neighbors[i] ] = 255;
			}

		}
	}


	// replace the current pixels
	pixel *oldPixels = mGrayPixels;
	mGrayPixels = temp;

	delete [] oldPixels;
}

