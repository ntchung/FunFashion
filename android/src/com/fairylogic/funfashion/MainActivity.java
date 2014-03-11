package com.fairylogic.funfashion;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.opengl.GLSurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.FrameLayout;
import android.widget.FrameLayout.*;
import android.view.Gravity;
import android.content.Intent;
import android.net.Uri;
import android.provider.MediaStore;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.os.Environment;
import android.graphics.BitmapFactory;
import java.io.File;

public class MainActivity extends Activity {

	private static final String NATIVE_LIB = "FunFashion";

	private static final int RESULT_LOAD_IMAGE_FROM_GALLERY = 1;
	private static final int RESULT_LOAD_IMAGE_FROM_CAMERA = 2;

	public native void createAssetManager(Object assetManager);

	public native void releaseAssetManager();

	public native void setBackgroundPicture(int[] pixels, int width, int height);
	
	public native void requestScreenShot(String filePath);

	static {
		System.loadLibrary(NATIVE_LIB);
	}

	private FashionGLView mGlView;
	private FashionRenderer mRenderer;

	private FrameLayout m_buttonsLayout;

	private String m_tempFilePath;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		createAssetManager(getAssets());
		m_tempFilePath = Environment.getExternalStorageDirectory()
				+ "/funfashion_temp_photo.jpg";

		setContentView(R.layout.activity_main);

		// Create OpenGL ES view:
		int depthSize = 16;
		int stencilSize = 1;
		boolean translucent = false;

		mGlView = new FashionGLView(this);
		mGlView.init(0, translucent, depthSize, stencilSize);

		mRenderer = new FashionRenderer();
		mGlView.setRenderer(mRenderer);

		mRenderer.mIsActive = true;
		mGlView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

		FrameLayout glLayout = (FrameLayout) findViewById(R.id.GLLayout);
		glLayout.addView(mGlView);

		Button btnGallery = (Button) findViewById(R.id.btnGallery);
		btnGallery.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent i = new Intent(
						Intent.ACTION_PICK,
						android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);

				startActivityForResult(i, RESULT_LOAD_IMAGE_FROM_GALLERY);
			}
		});

		Button btnCamera = (Button) findViewById(R.id.btnCamera);
		btnCamera.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				File file = new File(m_tempFilePath);
				Uri outputFileUri = Uri.fromFile(file);

				Intent i = new Intent(
						android.provider.MediaStore.ACTION_IMAGE_CAPTURE);
				i.putExtra(MediaStore.EXTRA_OUTPUT, outputFileUri);
				startActivityForResult(i, RESULT_LOAD_IMAGE_FROM_CAMERA);
			}
		});

		Button btnSave = (Button) findViewById(R.id.btnSave);
		btnSave.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				requestScreenShot(Environment.getExternalStorageDirectory() + "/test.tga");
			}
		});
	}

	/** The final call you receive before your activity is destroyed. */
	protected void onDestroy() {
		// DebugLog.LOGD("onDestroy");
		super.onDestroy();

		mRenderer.onActivityDestroy();

		releaseAssetManager();
		System.gc();
	}

	/** Called when the activity will start interacting with the user. */
	protected void onResume() {
		// DebugLog.LOGD("onResume");
		super.onResume();

		// Resume the GL view:
		if (mGlView != null) {
			mGlView.setVisibility(View.VISIBLE);
			mGlView.onResume();

			mGlView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
		}
	}

	/** Called when the system is about to start resuming a previous activity. */
	protected void onPause() {
		// DebugLog.LOGD("onPause");
		super.onPause();

		if (mGlView != null) {
			mGlView.setVisibility(View.INVISIBLE);
			mGlView.onPause();
		}
	}

	public void onWindowFocusChanged(boolean hasFocus) {
		super.onWindowFocusChanged(hasFocus);
	}

	public void onBackPressed() {
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);

		String picturePath = "";

		if (requestCode == RESULT_LOAD_IMAGE_FROM_GALLERY
				&& resultCode == RESULT_OK && null != data) {
			Uri selectedImage = data.getData();
			String[] filePathColumn = { MediaStore.Images.Media.DATA };

			Cursor cursor = getContentResolver().query(selectedImage,
					filePathColumn, null, null, null);
			cursor.moveToFirst();

			int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
			picturePath = cursor.getString(columnIndex);
			cursor.close();

		}

		if (requestCode == RESULT_LOAD_IMAGE_FROM_CAMERA) {
			picturePath = m_tempFilePath;
		}

		if (picturePath.length() > 0) {
			BitmapFactory.Options options = new BitmapFactory.Options();
			options.inSampleSize = 4;

			Bitmap bitmap = BitmapFactory.decodeFile(picturePath, options);

			int width = bitmap.getWidth();
			int height = bitmap.getHeight();
			int[] pixels = new int[width * height];
			bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

			setBackgroundPicture(pixels, width, height);
		}
	}
}
