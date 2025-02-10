win32 {
    DEFINES += WINDOWS_SPECIFIC_DEFINE
    LIBS += -LD:/work/FFmpeg/soft/ffmpeg-n4.4.2/lib -lavcodec -lavfilter -lavformat -lswscale -lavutil -lswresample -lavdevice
    INCLUDEPATH += D:/work/FFmpeg/soft/ffmpeg-n4.4.2/include
    DEPENDPATH += D:/work/FFmpeg/soft/ffmpeg-n4.4.2/include

}

macx {
    DEFINES += MAC_SPECIFIC_DEFINE

    # ******* Googletest *******
    GTEST_DIR = /Users/areay7/workspace/googletest

    INCLUDEPATH += $$GTEST_DIR/googletest/include
    LIBS += -L$$GTEST_DIR/build/lib -lgtest -lgtest_main

    message($$GTEST_DIR)
    # ******* Googletest *******

    # ******* VideoPlay *******
    # INCLUDEPATH += /usr/local/include/SDL2
    INCLUDEPATH += /usr/local/ffmpeg/include
    DEPENDPATH += /usr/local/ffmpeg/include

    # LIBS += -L/usr/local/lib/ -lSDL2
    LIBS += -L/usr/local/ffmpeg/lib -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale

    # ******* VideoPlay *******


    INCLUDEPATH += $$ROOT_DIR/3rd_party/libhpdf/include
    LIBS += -L$$ROOT_DIR/3rd_party/libhpdf/MacOS/arm64 -lhpdf

}

unix:!macx {
    # LIBS += -L/usr/local/path/to/linux/libs -lmylinuxlib
    # INCLUDEPATH += /usr/local/path/to/linux/includes
    # DEFINES += LINUX_SPECIFIC_DEFINE
}

android {
    # DEFINES += ANDROID_SPECIFIC_DEFINE

    # GTEST_DIR = /Users/areay7/workspace/googletest

    # INCLUDEPATH += $$GTEST_DIR/googletest/include
    # LIBS += -L$$GTEST_DIR/build/lib -lgtest -lgtest_main

    # message($$GTEST_DIR)

    # INCLUDEPATH += /usr/local/ffmpeg/include
    # DEPENDPATH += /usr/local/ffmpeg/include

    # LIBS += -L/usr/local/ffmpeg/lib -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale
}
