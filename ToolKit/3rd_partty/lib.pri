



win32 {
    # LIBS += -LC:/path/to/windows/libs -lmywindowslib
    # INCLUDEPATH += C:/path/to/windows/includes
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
