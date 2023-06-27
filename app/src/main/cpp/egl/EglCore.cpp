//
// Created by Macro on 2023/6/27.
//

#include "LogUtil.h"
#include "EglCore.h"
#include <assert.h>

EglCore::EglCore() {
    init(NULL, 0);
}

EglCore::~EglCore() {
    release();
}

EglCore::EglCore(EGLContext sharedContext, int flags) {
    init(sharedContext, flags);
}

/**
 *
 * @param sharedContext
 * @param flags
 * @return
 */
bool EglCore::init(EGLContext sharedContext, int flags) {
    assert(mEGLDisplay != EGL_NO_DISPLAY);
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        LOGCATE("EGL already set up");
        return false;
    }
    if (sharedContext == NULL) {
        sharedContext = EGL_NO_DISPLAY;
    }
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(mEGLDisplay != EGL_NO_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        LOGCATE("unable to get EGL14 display.\n");
        return false;
    }

    //尝试使用GLES3
    if ((flags & FLAG_TRY_GLES3) != 0) {
        EGLConfig config = getConfig(flags, 3);
        if (config != NULL) {
            int attrib3_list[] = {
                    EGL_CONTEXT_CLIENT_VERSION, 3,
                    EGL_NONE
            };

            EGLContext context = eglCreateContext(mEGLDisplay, config,
                                                  sharedContext, attrib3_list);

            checkEglError("eglCreateContext");
            if (eglGetError() == EGL_SUCCESS) {
                mEGLConfig = config;
                mEGLContext = context;
                mGlVersion = 3;
            }
        }
    }

    /**如果GLES3没有获取到，则尝试使用GLES2*/
    if (mEGLContext == EGL_NO_CONTEXT) {
        EGLConfig config = getConfig(flags, 2);
        assert(config != NULL);
        int attrib2_list[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2,
                EGL_NONE
        };
        EGLContext context = eglCreateContext(mEGLDisplay, config,
                                              sharedContext, attrib2_list);

        checkEglError("eglCreateContext");
        if (eglGetError() == EGL_SUCCESS) {
            mEGLConfig = config;
            mEGLContext = context;
            mGlVersion = 2;
        }
    }

    /**获取*/
    //todo 测试下传参对不对
    eglPresentationTimeAndroid = (EGL_PRESENTATION_TIME_ANDROIDPROC)
            eglGetProcAddress("eglPresentationTimeAndroid");
    if(!eglPresentationTimeAndroid){
        LOGCATE("eglPresentationTimeAndroid is not availab");
    }

    int values[1] = {0};
    eglQueryContext(mEGLDisplay,mEGLContext,EGL_CONTEXT_CLIENT_VERSION,values);
    LOGCATE("EGLContext created,client version %d",values[0]);
    return true;
}

/**
 *
 * @param flag
 * @param version
 * @return
 */
EGLConfig EglCore::getConfig(int flags, int version) {
    int renderableType = EGL_OPENGL_ES2_BIT;
    if(version >= 3){
        renderableType |= EGL_OPENGL_ES3_BIT_KHR;
    }
    int attribList[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE,8,
            EGL_RENDERABLE_TYPE,renderableType,
            EGL_NONE,0, // placeholder for recordable [@-3]
            EGL_NONE
    };

    int length = sizeof(attribList) / sizeof(attribList[0]);
    if((flags & FLAG_RECORDABLE) != 0){
        attribList[length - 3] = EGL_RECORDABLE_ANDROID;
        attribList[length -2] = 1;
    }
    EGLConfig configs = NULL;
    int numConfigs;
    if(!eglChooseConfig(mEGLDisplay,attribList,&configs,1,&numConfigs)){
        LOGCATE("unable to find RGB8888 / %d  EGLConfig", version);
        return NULL;
    }
    return configs;
}



