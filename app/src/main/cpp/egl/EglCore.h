//
// Created by Macro on 2023/6/27.
//

#ifndef OPENGLESPRAC_EGLCORE_H
#define OPENGLESPRAC_EGLCORE_H

#include <android/native_window.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

/**
 * Constructor flag: surface must be recordable.  This discourages EGL from using a
 * pixel format that cannot be converted efficiently to something usable by the video
 * encoder.
 */
#define FLAG_RECORDABLE 0x01

/**
 * Constructor flag: ask for GLES3, fall back to GLES2 if not available.  Without this
 * flag, GLES2 is used.
 */
#define FLAG_TRY_GLES3 002

// Android-specific extension
#define EGL_RECORDABLE_ANDROID 0x3142

typedef EGLBoolean (EGLAPIENTRYP EGL_PRESENTATION_TIME_ANDROIDPROC)(EGLDisplay display,EGLSurface surface,khronos_stime_nanoseconds_t time);
/**
 * opengles 生命周期相关流程的管理类
 */
class EglCore {

private:
    EGLDisplay mEGLDisplay = EGL_NO_DISPLAY;
    EGLConfig mEGLConfig = NULL;
    EGLContext mEGLContext = EGL_NO_CONTEXT;

    //设置时间戳方法
    EGL_PRESENTATION_TIME_ANDROIDPROC eglPresentationTimeAndroid = NULL;

    int mGlVersion = -1;

    EGLConfig  getConfig(int flag, int version);

public:
    EglCore();
    ~EglCore();
    EglCore(EGLContext sharedContext,int flags);
    bool init(EGLContext sharedContext,int flags);
    void release();

    EGLContext  getEGLContext();

    /**创建EGLSurface*/
    void releaseSurface(EGLSurface eglSurface);

    /**创建EGLSurface*/
    EGLSurface createWindowSurface(int width,int height);

    /**创建离屏EGLSurface*/
    EGLSurface createOffscreenSurface(int width,int height);

    /**切换到当前上下文*/
    void makeCurrent(EGLSurface eglSurface);

    /**切换到某个上下文*/
    void makeCurrent(EGLSurface drawSurface,EGLSurface readSurface);

    /**清除当前上下文*/
    void makeNothingCurrent();

    /**输出缓冲区*/
    bool swapBuffers(EGLSurface eglSurface);

    /**设置pts (显示事件)*/
    void setPresentationTime(EGLSurface eglSurface, long nsecs);

    /**判断是否属于当前上下文*/
    bool isCurrent(EGLSurface eglSurface);

    int querySurface(EGLSurface eglSurface,int what);

    const char *queryString(int what);
    /**获取当前GLES 版本号*/
    int getGlVersion();

    /**检查错误*/
    void checkEglError(const char *msg);
};
#endif //OPENGLESPRAC_EGLCORE_H
