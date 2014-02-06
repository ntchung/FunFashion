package com.fairylogic.funfashion;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.opengl.GLSurfaceView;

public class MainActivity extends Activity {
	
	private static final String NATIVE_LIB = "FunFashion"; 
	
	static
    {
        System.loadLibrary(NATIVE_LIB);
    }
	
	private FashionGLView mGlView;
	private FashionRenderer mRenderer;	
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Create OpenGL ES view:
        int depthSize = 16;
        int stencilSize = 1;
        boolean translucent = false;
        
        mGlView = new FashionGLView(this);
        mGlView.init(0, translucent, depthSize, stencilSize);
        
        mRenderer = new FashionRenderer();        
        mGlView.setRenderer(mRenderer);		
        
        mRenderer.mIsActive = true;
        mGlView.setRenderMode( GLSurfaceView.RENDERMODE_CONTINUOUSLY );

        setContentView(mGlView);
    }
    
    /** The final call you receive before your activity is destroyed.*/
    protected void onDestroy()
    {
        //DebugLog.LOGD("onDestroy");
        super.onDestroy();		
				
        System.gc();
    }
    
    /** Called when the activity will start interacting with the user.*/
    protected void onResume()
    {
        //DebugLog.LOGD("onResume");
        super.onResume();
        				
        // Resume the GL view:
        if (mGlView != null)
        {
            mGlView.setVisibility(View.VISIBLE);
            mGlView.onResume();
			
			mGlView.setRenderMode( GLSurfaceView.RENDERMODE_CONTINUOUSLY );
        }        		
    }
    
    /** Called when the system is about to start resuming a previous activity.*/
    protected void onPause()
    {
        //DebugLog.LOGD("onPause");
        super.onPause();
				
        if (mGlView != null)
        {
            mGlView.setVisibility(View.INVISIBLE);
            mGlView.onPause();
        }				
    }
    
    public void onWindowFocusChanged( boolean hasFocus )
	{
		super.onWindowFocusChanged( hasFocus );
	}
    
    public void onBackPressed() 
	{
    }
}
