cmake_minimum_required(VERSION 3.2)

project(ToolKit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/ui")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FFmpegHeaders /usr/local/ffmpeg/include)

find_package(Qt6 COMPONENTS Widgets  Sql  REQUIRED)
# find_package(Qt5 COMPONENTS Widgets Network Sql  REQUIRED)

add_subdirectory(3rd_party)
add_subdirectory(3rd_party/QXlsx)

include_directories(
    ${CMAKE_SOURCE_DIR}/3rd_party/FFmpeg/include
    ${CMAKE_SOURCE_DIR}/3rd_party/Opencv/include
    ${CMAKE_SOURCE_DIR}/3rd_party/QXlsx/header
    ${FFmpegHeaders}
)

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/VideoPlay
    ${CMAKE_SOURCE_DIR}/include/Xlsx
)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/VideoPlay/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Xlsx/*.cpp
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

target_link_libraries(ToolKit PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql QXlsx)

install(TARGETS ToolKit DESTINATION ${CMAKE_SOURCE_DIR}/bin)




