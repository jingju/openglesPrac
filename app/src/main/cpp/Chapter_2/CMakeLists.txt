# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

set(COMMON_PATH ../Common)

set(COMMON_INC_PATH ${COMMON_PATH}/Include)
set(COMMON_SRC_PATH ${COMMON_PATH}/Source)

add_library(
        Hello_Triangle

        SHARED

        ${COMMON_SRC_PATH}/esShader.c
        ${COMMON_SRC_PATH}/esShapes.c
        ${COMMON_SRC_PATH}/esTransform.c
        ${COMMON_SRC_PATH}/esUtil.c
        ${COMMON_SRC_PATH}/Android/esUtil_Android.c
        Hello_Triangle.c
)
#todo 添加ndk的  android_native_app_glue.c文件的的一个库
add_library(app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

#set(CMAKE_SHARED_LINKER_FLAGS
#        "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")


# 添加头文件路径
include_directories(
        ${COMMON_INC_PATH}
        ${ANDROID_NDK}/sources/android/native_app_glue
        )

target_link_libraries(
        Hello_Triangle
        app_glue
        log
        android
        EGL
        GLESv3
        )




