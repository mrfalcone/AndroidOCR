package com.ocr;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ImageView.ScaleType;
import android.widget.TextView;

public class OCRMain extends Activity implements Camera.PreviewCallback {
	
	
	
	private Camera mCam;
	
	
	private ImageView mOverlayImageView;
	
	private SurfaceView mSurface;
	
	private SurfaceHolder mHolder;
	

	Bitmap mOverlayBitmap = null;

	boolean mIsFiltering = true;
	
	private String mDatapath;
	
	private TextView mRecogTextView;
	

	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        
        getWindow().setFormat(PixelFormat.TRANSLUCENT);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,

        WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        
        setContentView(R.layout.main);
        

        installDataFiles();
        

        
        
        mOverlayImageView = (ImageView)findViewById(R.id.overlayImageView);
        
        
        mSurface = (SurfaceView)findViewById(R.id.previewView);
        
        
        mRecogTextView = (TextView)findViewById(R.id.recogTextView);
        

        mHolder = mSurface.getHolder();

    
        mHolder.addCallback(mSurfaceCallback);

        mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

        
        Button filterButton = (Button)findViewById(R.id.toggleButton);
        
        filterButton.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				
				OCRMain.this.mIsFiltering = !(OCRMain.this.mIsFiltering);
				
				setIsFiltering(OCRMain.this.mIsFiltering);
				
				if(OCRMain.this.mIsFiltering)
					((Button)v).setText("Use Method 2");
				else
					((Button)v).setText("Use Method 1");
			}
        	
        });

        
        
        Button focusButton = (Button)findViewById(R.id.autoFocusButton);
        
        focusButton.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				
				mCam.autoFocus(null);
			}
        	
        });

    }
    
    
    
    SurfaceHolder.Callback mSurfaceCallback = new SurfaceHolder.Callback(){

		@Override
		public void surfaceChanged(SurfaceHolder holder, int format, int width,
				int height) {

			

			mOverlayBitmap = Bitmap.createBitmap(width, width, Bitmap.Config.ARGB_8888);
			
			
			Log.e("GOOD","about to init androidocr with path: " + mDatapath);
			
				try {
					if(initAndroidOCR(width, width, true, mDatapath, null) < 0)
						throw new Exception("Error initializing OCR engine.");
					
				} catch (Exception e) {

					e.printStackTrace();
				}
			
			
				Log.e("GOOD","about to set preview size");
			
			Camera.Parameters cp = mCam.getParameters();
			cp.setPreviewSize(width, width);
			
			
			//cp.setPreviewFrameRate(60);
			
			
			mCam.setParameters(cp);
			
			
			
			
			
			mCam.setDisplayOrientation(90);
			
			
			mCam.startPreview();

		}

		@Override
		public void surfaceCreated(SurfaceHolder holder) {
			
			Log.e("GOOD","about to init cam");
			
			try{
				mCam = Camera.open();
			}
			catch (Exception e){
				e.printStackTrace();
			}
			
			
			
			try {
				mCam.setPreviewDisplay(mHolder);
				
				mCam.setPreviewCallback(OCRMain.this);
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			
			Log.e("GOOD","surface created");
		
		}

		@Override
		public void surfaceDestroyed(SurfaceHolder holder) {
			
				mCam.stopPreview();
				mCam.setPreviewCallback(null);
				mCam.release();
			
		}
    	
    };
    
    
    
    
    private void installDataFiles(){
    	
    	File extDir = getExternalFilesDir(null);
    	
    	String datapath = extDir.getAbsolutePath() + "/tessdata";
    	
    	mDatapath = datapath;
    	
    	
    	File dataDir = new File(datapath);
    	File configDir = new File(datapath + "/config");
    	File tessDir = new File(datapath + "/tessconfigs");
    	
    	
    	// if the data dir already exists, skip installing
    	if(!dataDir.mkdirs())
    		return;
    	

    	
    	Log.e("INSTALL", "Installing data files...");
    	
    	installFile(R.raw.eng, datapath + "/eng.traineddata");
    	
    	
		if (configDir.mkdirs()) {

			datapath = configDir.getAbsolutePath();

			installFile(R.raw.config_ambigs, datapath + "/ambigs.train");
			installFile(R.raw.config_api_config, datapath + "/api_config");
			installFile(R.raw.config_box, datapath + "/box.train.stderr");
			installFile(R.raw.config_boxt, datapath + "/box.train");
			installFile(R.raw.config_digits, datapath + "/digits");
			installFile(R.raw.config_inter, datapath + "/inter");
			installFile(R.raw.config_kannada, datapath + "/kannada");
			installFile(R.raw.config_logfile, datapath + "/logfile");
			installFile(R.raw.config_makebox, datapath + "/makebox");
			installFile(R.raw.config_unlv, datapath + "/unlv");
			
			Log.e("INSTALL", "config/ files installed.");
		}
    	
		
		if (tessDir.mkdirs()) {

			datapath = tessDir.getAbsolutePath();

			installFile(R.raw.tessconfigs_batch, datapath + "/batch");
			installFile(R.raw.tessconfigs_batchn, datapath + "/batch.nochop");
			installFile(R.raw.tessconfigs_matdemo, datapath + "/matdemo");
			installFile(R.raw.tessconfigs_msdemo, datapath + "/msdemo");
			installFile(R.raw.tessconfigs_nobatch, datapath + "/nobatch");
			installFile(R.raw.tessconfigs_segdemo, datapath + "/segdemo");
			
			Log.e("INSTALL", "tessconfig/ files installed.");
		}

    	
    }
    
    
    private void installFile(int resId, String absFilename){
    	
    	try{
	    	OutputStream os = new FileOutputStream(absFilename);
			
			InputStream is = getResources().openRawResource(resId);
			
			byte[] data = new byte[is.available()];
			
			is.read(data);
			
			os.write(data);
			
			is.close();
			
			os.flush();
			os.close();
			
    	}
    	catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
    }
    

    
  
	@Override
	public void onPreviewFrame(byte[] data, Camera camera) {
		

		//camera.autoFocus(null);


		processBitmapOverlay(data, mOverlayBitmap);
		
		mRecogTextView.setText(getImageText());
		
		mOverlayImageView.setImageBitmap(mOverlayBitmap);

		mOverlayImageView.setScaleType(ScaleType.CENTER_CROP);

		//mOverlayImageView.setVisibility(View.INVISIBLE);
		
	}
    
	
	public native int initAndroidOCR(int overlayWidth, int overlayHeight, boolean rotate, String tessDir, String tessLang);
	public native void processBitmapOverlay(byte[] imageData, Bitmap overlay);
	public native String getImageText();
	public native void setIsFiltering(boolean filter);
	
	
	public native void startProfile();
	public native void endProfile();
	
	
	
	static{
		
		System.loadLibrary("lept");
		System.loadLibrary("tess");
		System.loadLibrary("AndroidOCR");
		
		
	}

	
	@Override
	public void onResume(){
		super.onResume();
		
		Log.e("PROF", "Starting profiling...");
		startProfile();
		Log.e("PROF", "Profiling started.");
	}
	
	@Override
	public void onPause(){
		super.onPause();
		
		endProfile();
	}
	
	
}

// todo
// fix magic numbers

// ocr should require size multiple of 3*2 + 2 if using 3x3 neighborhoods
// -- require square image size

// ocr should use bitmap api in android, edit bitmap in place??

// smart auto focus

// save some preview captures to use for development

// camera zoom
// remove extra garbage from character recognition
// set ocr precision level??


// bugs:
// image isn't being stretched when rotated, must keep width and height equal
// --rotation works but width and height do not get changed
// surface view can't be smaller than width of the screen
// -- should get supported sizes, set to aspect ratio of 1:1

