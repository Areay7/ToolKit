win32 {
    DEFINES += WINDOWS_SPECIFIC_DEFINE

    # ******* VideoPlay *******
    LIBS += -L$$ROOT_DIR/3rd_party/FFmpeg/win/win64 -lavcodec -lavfilter -lavformat -lswscale -lavutil -lswresample -lavdevice
    INCLUDEPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    DEPENDPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    # ******* VideoPlay *******

    # ******* hpdf *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/libhpdf/include
    LIBS += -L$$ROOT_DIR/3rd_party/libhpdf/win/win64 -lhpdf
    # ******* hpdf *******

    # ******* Opencv *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceDetector/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceLandmarker/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceRecognizer/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceTracker/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/QualityAssessor/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/SeetaNet/include

    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/win/win64 -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer -lSeetaFaceTracker -lSeetaNet -lSeetaQualityAssessor
    # ******* Opencv *******

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
    INCLUDEPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    DEPENDPATH += $$ROOT_DIR/3rd_party/FFmpeg/include

    # LIBS += -L/usr/local/lib/ -lSDL2
    LIBS += -L$$ROOT_DIR/3rd_party/FFmpeg/MacOS/arm64 -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale
    # ******* VideoPlay *******

    # ******* hpdf *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/libhpdf/include
    LIBS += -L$$ROOT_DIR/3rd_party/libhpdf/MacOS/arm64 -lhpdf
    # ******* hpdf *******

    # ******* Opencv *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceDetector/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceLandmarker/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceRecognizer/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceTracker/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/QualityAssessor/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/SeetaNet/include

    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/MacOS/arm64 -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer -lSeetaFaceTracker -lSeetaNet -lSeetaQualityAssessor
    # ******* Opencv *******

    # ******* Mqtt *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/QtMqtt/6.5.3/include
    LIBS += -L$$ROOT_DIR/3rd_party/QtMqtt/6.5.3/MacOS/arm64 -lQtMqtt
    # ******* Mqtt *******

}

unix:!macx {

    # DEFINES += LINUX_SPECIFIC_DEFINE

    # ******* VideoPlay *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    DEPENDPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    LIBS += -L$$ROOT_DIR/3rd_party/FFmpeg/Linux/amd64 -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale -lx264 -lfdk-aac
    # ******* VideoPlay *******

    # ******* hpdf *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/libhpdf/include
    LIBS += -L$$ROOT_DIR/3rd_party/libhpdf/Linux/amd64 -lhpdf
    # ******* hpdf *******
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
