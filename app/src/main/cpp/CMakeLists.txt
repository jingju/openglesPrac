# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)
# 设置GCC编译器的编译选项
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations -Wmissing-prototypes  -DANDROID")
endif(CMAKE_COMPILER_IS_GNUCC)

# 设置clang编译器的编译选项
if(CMAKE_COMPILER_IS_CLANG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-declarations -Wmissing-prototypes -Wdocumentation -Wunreachable-code  -DANDROID")
endif(CMAKE_COMPILER_IS_CLANG)
# common 不应放这里
add_subdirectory(${CMAKE_SOURCE_DIR}/Chapter_2)



