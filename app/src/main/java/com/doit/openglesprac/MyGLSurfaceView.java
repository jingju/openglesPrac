package com.doit.openglesprac;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

/**
 * @author: Macro
 * @description:
 * @email: zhaoguangju@situdata.com
 * @date: 2023/6/28
 */
public class MyGLSurfaceView extends GLSurfaceView implements ScaleGestureDetector.OnScaleGestureListener {
    private final float TOUCH_SCALE_FACTOR = 180.0f / 320;

    public static final int IMAGE_FORMAT_RGBA = 0x01;
    public static final int IMAGE_FORMAT_NV21 = 0x02;
    public static final int IMAGE_FORMAT_NV12 = 0x03;
    public static final int IMAGE_FORMAT_I420 = 0x04;
    public static final int IMAGE_FORMAT_YUYV = 0x05;
    public static final int IMAGE_FORMAT_GARY = 0x06;

    private float mPreviousY;
    private float mPreviousX;
    private int mXAngle;
    private int mYAngle;

    private MyGLRender mGLRender;

    private int mRatioWidth = 0;
    private int mRatioHeight = 0;

    private ScaleGestureDetector mScaleGestureDetector;
    private float mPreScale = 1.0f;
    private float mCurScale = 1.0f;
    private long mLastMultiTouchTime;

    public MyGLSurfaceView(Context context, MyGLRender glRender) {
        this(context, glRender, null);
    }

    public MyGLSurfaceView(Context context, MyGLRender glRender, AttributeSet attrs) {
        super(context, attrs);
        this.setEGLContextClientVersion(2);
        setEGLConfigChooser(8,8,8,8,16,8);
        setRenderer(mGLRender);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
        mScaleGestureDetector = new ScaleGestureDetector(context,this);
    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        //如果是单指触控
        // TODO: 2023/6/28 未完
        if(e.getPointerCount() == 1){
            consumeTouchEvent(e);
        }
        return super.onTouchEvent(e);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }

    public void setAspectRatio(int with, int height){
        // TODO: 2023/6/28
    }

    public MyGLRender getGLRender(){return mGLRender;}

    @Override
    public boolean onScale(ScaleGestureDetector detector) {
        // TODO: 2023/6/28
        return false;
    }

    @Override
    public boolean onScaleBegin(ScaleGestureDetector detector) {
        // TODO: 2023/6/28
        return false;
    }

    @Override
    public void onScaleEnd(ScaleGestureDetector detector) {
        // TODO: 2023/6/28
    }

    public void consumeTouchEvent(MotionEvent e){
        dealClickEvent(e);
        // TODO: 2023/6/28
    }

    public void dealClickEvent(MotionEvent e){
        // TODO: 2023/6/28 暂时不处理
        float touchX = -1, touchY = -1;
        switch (e.getAction()){
            case MotionEvent.ACTION_UP:
                touchX = e.getX();
                touchY = e.getY();
        }
    }
}
