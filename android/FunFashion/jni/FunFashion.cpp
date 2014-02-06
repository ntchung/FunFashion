#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define NULL 0
#define LOG(...)	__android_log_print(ANDROID_LOG_INFO, "FunFashion", __VA_ARGS__)

#ifdef __cplusplus
extern "C"
{
#endif

JavaVM* gJVM;

// Screen dimensions:
unsigned int screenWidth = 0;
unsigned int screenHeight = 0;

bool isGameInited;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	LOG("JNI_OnLoad");
	gJVM = jvm;  // cache the JavaVM pointer
	
	JNIEnv *env;
	int status = gJVM->GetEnv((void **)&env, JNI_VERSION_1_6);
	
	if(status < 0)
	{
		LOG("Failed to get JNI environment, assuming native thread");
		status = gJVM->AttachCurrentThread(&env, NULL);
		if(status < 0)
		{
			LOG("callback_handler: failed to attach current thread");
			return 0;
		}
	}	
	
	isGameInited = false;
	
	return JNI_VERSION_1_6;
}

JNIEnv* getJNIEnv()
{
	JNIEnv *env;
	int status = gJVM->GetEnv((void **)&env, JNI_VERSION_1_6);
	if(status < 0)
	{
		LOG("Failed to get JNI environment, assuming native thread");
		status = gJVM->AttachCurrentThread(&env, NULL);
		if(status < 0)
		{
			LOG("callback_handler: failed to attach current thread");
			return 0;
		}
	}
	
	return env;
}

#define JNI_RENDERER_NAME(func) Java_com_fairylogic_funfashion_FashionRenderer_##func

JNIEXPORT void JNICALL
JNI_RENDERER_NAME(updateFrame)(JNIEnv *, jobject)
{	
	if( isGameInited )
	{		
		// TODO
	}	
}

JNIEXPORT void JNICALL
JNI_RENDERER_NAME(renderFrame)(JNIEnv *, jobject)
{	
	glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE );
	glClearColor( 0.0f, 0.0f, 1.0f, 0.0f );	
	glEnable( GL_DEPTH_TEST );	
	glDepthMask( GL_TRUE );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		
	
	// TODO
}

JNIEXPORT void JNICALL
JNI_RENDERER_NAME(initRendering)(JNIEnv* env, jobject obj)
{
    LOG("initRendering");

    // Define clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	
	if( !isGameInited )
	{		
		// TODO
		isGameInited = true;
	}
	
	// TODO
}


JNIEXPORT void JNICALL
JNI_RENDERER_NAME(updateRendering)(
                        JNIEnv* env, jobject obj, jint width, jint height)
{
    LOG("updateRendering");

    // Update screen dimensions
    screenWidth = width;
    screenHeight = height;
	
	LOG("Screen (%d,%d)", screenWidth, screenHeight );
	
	// TODO
}

#ifdef __cplusplus
}
#endif