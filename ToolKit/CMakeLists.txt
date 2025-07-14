cmake_minimum_required(VERSION 3.2)

project(ToolKit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FFmpegHeaders /opt/homebrew/Cellar/ffmpeg@4/4.4.5_4)
set(FFMPEG_LIB_DIR /opt/homebrew/Cellar/ffmpeg@4/4.4.5_4/lib)
set(OPENCV_LIB_DIR /opt/homebrew/opt/opencv@4/lib)

set(OPENCV_EXTRA_LIB_DIR ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/lib/MacOS/arm64)
set(MQTT_LIB_DIR ${CMAKE_SOURCE_DIR}/3rd_party/QtMqtt/6.5.3/MacOS/arm64)
set(HARU_LIB_DIR ${CMAKE_SOURCE_DIR}/3rd_party/libhpdf/MacOS/arm64)


find_package(Qt6 COMPONENTS Widgets Sql Multimedia Core5compat REQUIRED)
# find_package(Qt5 COMPONENTS Widgets Network Sql  REQUIRED)

add_subdirectory(3rd_party)
add_subdirectory(3rd_party/QXlsx)

include_directories(
    ${CMAKE_SOURCE_DIR}/3rd_party/FFmpeg/include
    # ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include
    ${OPENCV_LIB_DIR}/../include/opencv4
    ${CMAKE_SOURCE_DIR}/3rd_party/QXlsx/header
    ${CMAKE_SOURCE_DIR}/3rd_party/libhpdf/include
    ${CMAKE_SOURCE_DIR}/3rd_party/QtMqtt/6.5.3/include
    ${FFmpegHeaders}

    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceDetector/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceLandmarker/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceRecognizer/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceTracker/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/QualityAssessor/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/SeetaNet/include
)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/VideoPlay
    ${CMAKE_SOURCE_DIR}/include/OpencvServer 
    ${CMAKE_SOURCE_DIR}/include/Xlsx
    ${CMAKE_SOURCE_DIR}/include/QPS
    ${CMAKE_SOURCE_DIR}/include/PDF
    ${CMAKE_SOURCE_DIR}/include/Mqtt
)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/VideoPlay/*.cpp
    ${CMAKE_SOURCE_DIR}/src/OpencvServer/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Xlsx/*.cpp
    ${CMAKE_SOURCE_DIR}/src/QPS/*.cpp
    ${CMAKE_SOURCE_DIR}/src/PDF/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Mqtt/*.cpp
    ${CMAKE_SOURCE_DIR}/test/*.cpp
)

file(GLOB_RECURSE HEADERS
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/include/VideoPlay/*.h
    ${CMAKE_SOURCE_DIR}/include/Xlsx/*.h
)

file(GLOB_RECURSE FORMS 
    ${CMAKE_SOURCE_DIR}/ui/*.ui
)

file(GLOB_RECURSE RESOURCES 
    ${CMAKE_SOURCE_DIR}/*.qrc
)

qt_add_executable(ToolKit
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${RESOURCES}
)


target_compile_definitions(ToolKit PRIVATE PRO_FILE_PWD="${CMAKE_SOURCE_DIR}")

target_link_libraries(ToolKit PRIVATE
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql Qt6::Multimedia Qt6::Core5Compat
    QXlsx

    ${MQTT_LIB_DIR}/libQtMqtt.dylib
    ${HARU_LIB_DIR}/libhpdf.dylib

    ${OPENCV_LIB_DIR}/libopencv_core.dylib
    ${OPENCV_LIB_DIR}/libopencv_imgproc.dylib
    ${OPENCV_LIB_DIR}/libopencv_videoio.dylib
    ${OPENCV_LIB_DIR}/libopencv_highgui.dylib
    ${OPENCV_LIB_DIR}/libopencv_imgcodecs.dylib

    ${OPENCV_EXTRA_LIB_DIR}/libSeetaFaceDetector.dylib
    ${OPENCV_EXTRA_LIB_DIR}/libSeetaFaceLandmarker.dylib
    ${OPENCV_EXTRA_LIB_DIR}/libSeetaFaceRecognizer.dylib
    ${OPENCV_EXTRA_LIB_DIR}/libSeetaFaceTracker.dylib
    ${OPENCV_EXTRA_LIB_DIR}/libSeetaNet.dylib
    ${OPENCV_EXTRA_LIB_DIR}/libSeetaQualityAssessor.dylib

    ${FFMPEG_LIB_DIR}/libavcodec.dylib
    ${FFMPEG_LIB_DIR}/libavdevice.dylib
    ${FFMPEG_LIB_DIR}/libavfilter.dylib
    ${FFMPEG_LIB_DIR}/libavformat.dylib
    ${FFMPEG_LIB_DIR}/libavresample.dylib
    ${FFMPEG_LIB_DIR}/libavutil.dylib
    ${FFMPEG_LIB_DIR}/libswresample.dylib
    ${FFMPEG_LIB_DIR}/libswscale.dylib
    ${FFMPEG_LIB_DIR}/libpostproc.dylib
)

install(TARGETS ToolKit DESTINATION ${CMAKE_SOURCE_DIR}/bin)




