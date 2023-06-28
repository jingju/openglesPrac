package com.doit.openglesprac.egl;

/**
 * @author: Macro
 * @description:
 * @email: zhaoguangju@situdata.com
 * @date: 2023/6/28
 */
public class NativeEglRender {
    public native void native_EglRenderInit();

    public native void native_EglRenderSetImageData(byte[] data, int width, int height);

    public native void native_EglRenderSetIntParams(int paramType, int param);

    public native void native_EglRenderDraw();

    public native void native_EglRenderUnInit();
}
