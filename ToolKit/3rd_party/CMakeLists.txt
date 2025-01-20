cmake_minimum_required(VERSION 3.2)

# 子项目名称
project(VideoPlayLib VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找平台相关定义和库
if(WIN32)
    add_definitions(-DWINDOWS_SPECIFIC_DEFINE)

    # 添加 FFmpeg 的路径（Windows）
    include_directories(D:/work/FFmpeg/soft/ffmpeg-n4.4.2/include)
    link_directories(D:/work/FFmpeg/soft/ffmpeg-n4.4.2/lib)
    set(FFMPEG_LIBS
        avcodec
        avfilter
        avformat
        swscale
        avutil
        swresample
        avdevice
    )
elseif(APPLE)
    add_definitions(-DMAC_SPECIFIC_DEFINE)

    # 添加 FFmpeg 和 GTest 的路径（macOS）
    set(GTEST_DIR /Users/areay7/workspace/googletest)
    include_directories(${GTEST_DIR}/googletest/include)
    link_directories(${GTEST_DIR}/build/lib)

    # 添加 FFmpeg 的路径（macOS）
    include_directories(/usr/local/ffmpeg/include)
    link_directories(/usr/local/ffmpeg/lib)

    set(FFMPEG_LIBS
        avformat
        avcodec
        avdevice
        avfilter
        avutil
        postproc
        swresample
        swscale
    )

    # 由于您是使用动态库 (.dylib)，可能需要链接到具体的版本
    set(FFMPEG_LIBS
        ${FFMPEG_LIBS}
        /usr/local/ffmpeg/lib/libavcodec.58.dylib
        /usr/local/ffmpeg/lib/libavformat.58.dylib
        /usr/local/ffmpeg/lib/libavutil.56.dylib
        /usr/local/ffmpeg/lib/libswscale.5.dylib
        /usr/local/ffmpeg/lib/libswresample.3.dylib
        /usr/local/ffmpeg/lib/libpostproc.55.dylib
        /usr/local/ffmpeg/lib/libavdevice.58.dylib
    )
elseif(UNIX AND NOT APPLE)
    # 添加 Linux 平台的路径和定义
    add_definitions(-DLINUX_SPECIFIC_DEFINE)

    # 示例路径，替换为您的实际路径
    include_directories(/usr/local/path/to/linux/includes)
    link_directories(/usr/local/path/to/linux/libs)
    set(FFMPEG_LIBS
        mylinuxlib
    )
endif()

# 查找源文件和头文件
file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

# 定义库
add_library(VideoPlayLib STATIC ${SOURCES} ${HEADERS})

# 链接 FFmpeg 库
target_link_libraries(VideoPlayLib PRIVATE ${FFMPEG_LIBS})

# 添加头文件路径
target_include_directories(VideoPlayLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 打印调试信息
message(STATUS "VideoPlayLib sources: ${SOURCES}")
message(STATUS "VideoPlayLib headers: ${HEADERS}")
message(STATUS "FFmpeg libraries: ${FFMPEG_LIBS}")