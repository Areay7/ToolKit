cmake_minimum_required(VERSION 3.14)

project(ToolKit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")

# Detect platform
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(PLATFORM macOS)
elseif(WIN32)
    set(PLATFORM Windows)
elseif(UNIX)
    set(PLATFORM Linux)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# Path configurations
if(${PLATFORM} STREQUAL "macOS")
    set(FFMPEG_LIB_DIR "/opt/homebrew/Cellar/ffmpeg@4/4.4.5_4/lib")
    set(OPENCV_LIB_DIR "/opt/homebrew/opt/opencv@4/lib")
    set(OPENCV_INCLUDE_DIR "${OPENCV_LIB_DIR}/../include/opencv4")
    set(MQTT_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/QtMqtt/6.5.3/MacOS/arm64")
    set(HARU_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/libhpdf/MacOS/arm64")
    set(SEETA_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/Opencv/lib/MacOS/arm64")
elseif(${PLATFORM} STREQUAL "Windows")
    set(FFMPEG_LIB_DIR "C:/libs/ffmpeg/lib")
    set(OPENCV_LIB_DIR "C:/libs/opencv/lib")
    set(OPENCV_INCLUDE_DIR "C:/libs/opencv/include")
    set(MQTT_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/QtMqtt/6.5.3/Windows/x64")
    set(HARU_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/libhpdf/Windows/x64")
    set(SEETA_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/Opencv/lib/Windows/x64")
elseif(${PLATFORM} STREQUAL "Linux")
    set(FFMPEG_LIB_DIR "/usr/lib/x86_64-linux-gnu")
    set(OPENCV_LIB_DIR "/usr/lib/x86_64-linux-gnu")
    set(OPENCV_INCLUDE_DIR "/usr/include/opencv4")
    set(MQTT_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/QtMqtt/6.5.3/Linux/x64")
    set(HARU_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/libhpdf/Linux/x64")
    set(SEETA_LIB_DIR "${CMAKE_SOURCE_DIR}/3rd_party/Opencv/lib/Linux/x64")
endif()

if(NOT DEFINED FFMPEG_ROOT)
    set(FFMPEG_ROOT /opt/homebrew/opt/ffmpeg)
endif()

if(NOT DEFINED OPENCV_ROOT)
    set(OPENCV_ROOT /opt/homebrew/opt/opencv)
endif()

# Qt
find_package(Qt6 COMPONENTS Widgets Sql Multimedia Core5Compat REQUIRED)

# Subdirectories
add_subdirectory(3rd_party)
add_subdirectory(3rd_party/QXlsx)

# Include directories
include_directories(
    ${OPENCV_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3rd_party/FFmpeg/include
    ${CMAKE_SOURCE_DIR}/3rd_party/QXlsx/header
    ${CMAKE_SOURCE_DIR}/3rd_party/libhpdf/include
    ${CMAKE_SOURCE_DIR}/3rd_party/QtMqtt/6.5.3/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/VideoPlay
    ${CMAKE_SOURCE_DIR}/include/OpencvServer
    ${CMAKE_SOURCE_DIR}/include/Xlsx
    ${CMAKE_SOURCE_DIR}/include/QPS
    ${CMAKE_SOURCE_DIR}/include/PDF
    ${CMAKE_SOURCE_DIR}/include/Mqtt

    # SeetaFace2 includes
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceDetector/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceLandmarker/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceRecognizer/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/FaceTracker/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/QualityAssessor/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include/SeetaFace2/SeetaNet/include
)

# Source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/**/*.cpp ${CMAKE_SOURCE_DIR}/src/*.cpp  ${CMAKE_SOURCE_DIR}/test/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/**/*.h ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE FORMS ${CMAKE_SOURCE_DIR}/ui/*.ui)
file(GLOB_RECURSE RESOURCES ${CMAKE_SOURCE_DIR}/*.qrc)


# Executable
qt_add_executable(ToolKit ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})

# Definitions
target_compile_definitions(ToolKit PRIVATE PRO_FILE_PWD="${CMAKE_SOURCE_DIR}")

# Function to link libraries
function(link_lib_if_exists target libname path)
    find_library(${libname}_LIB ${libname} PATHS ${path} NO_DEFAULT_PATH)
    if(${libname}_LIB)
        target_link_libraries(${target} PRIVATE ${${libname}_LIB})
    else()
        message(FATAL_ERROR "Library ${libname} not found in ${path}")
    endif()
endfunction()

# QtMqtt and HaruPDF
link_lib_if_exists(ToolKit QtMqtt ${MQTT_LIB_DIR})
link_lib_if_exists(ToolKit hpdf ${HARU_LIB_DIR})

# OpenCV
foreach(lib IN ITEMS opencv_core opencv_imgproc opencv_videoio opencv_highgui opencv_imgcodecs)
    link_lib_if_exists(ToolKit ${lib} ${OPENCV_LIB_DIR})
endforeach()

# SeetaFace
foreach(lib IN ITEMS SeetaFaceDetector SeetaFaceLandmarker SeetaFaceRecognizer SeetaFaceTracker SeetaNet SeetaQualityAssessor)
    link_lib_if_exists(ToolKit ${lib} ${SEETA_LIB_DIR})
endforeach()

# FFmpeg
foreach(lib IN ITEMS avcodec avdevice avfilter avformat avresample avutil swresample swscale postproc)
    link_lib_if_exists(ToolKit ${lib} ${FFMPEG_LIB_DIR})
endforeach()

# Qt official libs
target_link_libraries(ToolKit PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql Qt6::Multimedia Qt6::Core5Compat QXlsx)

# Install
install(TARGETS ToolKit DESTINATION ${CMAKE_SOURCE_DIR}/bin)

