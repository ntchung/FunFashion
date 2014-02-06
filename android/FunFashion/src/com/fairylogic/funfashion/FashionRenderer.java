package com.fairylogic.funfashion;

import android.opengl.GLSurfaceView.Renderer;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class FashionRenderer implements GLSurfaceView.Renderer
{
	public boolean mIsActive = false;
    
    /** Native function for initializing the renderer. */
    public native void initRendering();    
    
    /** Native function to update the renderer. */
    public native void updateRendering(int width, int height);
    
    /** The native render function. */    
    public native void renderFrame();
    public native void updateFrame();
    
    private long startRenderTime;
	private long endRenderTime;
	private long deltaRenderTime;	
    
    /** Called when the surface is created or recreated. */
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        // Call native function to initialize rendering:
        initRendering();
        
		startRenderTime = System.currentTimeMillis();		
    }
    
    
    /** Called when the surface changed size. */
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        // Call native function to update rendering when render surface parameters have changed:
        updateRendering(width, height);

		startRenderTime = System.currentTimeMillis();
    }    
	
    /** Called to draw the current frame. */
    public void onDrawFrame(GL10 gl)
    {
		try
		{
			if (!mIsActive)
			{		
				Thread.sleep( 100 );
				Thread.yield();
				return;
			}
				
			endRenderTime = System.currentTimeMillis();
			deltaRenderTime = 33 - ( endRenderTime - startRenderTime );
			if( deltaRenderTime < 0 || deltaRenderTime > 33 )
			{
				deltaRenderTime = 33;
			}
			Thread.sleep( deltaRenderTime );
			
			startRenderTime = System.currentTimeMillis();
		}
		catch( Exception ex )
		{
			return;
		}
			
        // Call our native function to render content		
		updateFrame();		
		renderFrame();		
		
		Thread.yield();
    }
}
