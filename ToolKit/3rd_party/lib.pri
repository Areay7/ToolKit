

# SOURCES += \
#         $$PRO_FILE_PATH/src/VideoPlay/videodecode.cpp

# HEADERS += \
#         $$PRO_FILE_PATH/include/VideoPlay/videodecode.h


win32 {
    LIBS += -LD:/work/FFmpeg/soft/ffmpeg-n4.4.2/lib -lavcodec -lavfilter -lavformat -lswscale -lavutil -lswresample -lavdevice
    INCLUDEPATH += D:/work/FFmpeg/soft/ffmpeg-n4.4.2/include
    DEPENDPATH += D:/work/FFmpeg/soft/ffmpeg-n4.4.2/include
    # DEFINES += WINDOWS_SPECIFIC_DEFINE
}

macx {
    DEFINES += MAC_SPECIFIC_DEFINE

    # INCLUDEPATH += /usr/local/include/SDL2
    INCLUDEPATH += /usr/local/ffmpeg/include
    DEPENDPATH += /usr/local/ffmpeg/include

    # LIBS += -L/usr/local/lib/ -lSDL2
    LIBS += -L/usr/local/ffmpeg/lib -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale

}

unix:!macx {
    # LIBS += -L/usr/local/path/to/linux/libs -lmylinuxlib
    # INCLUDEPATH += /usr/local/path/to/linux/includes
    # DEFINES += LINUX_SPECIFIC_DEFINE
}
