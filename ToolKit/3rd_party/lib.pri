win32 {
    DEFINES += WINDOWS_SPECIFIC_DEFINE

    # ******* VideoPlay *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    DEPENDPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    LIBS += -L$$ROOT_DIR/3rd_party/FFmpeg/lib/win/win64 -lavcodec -lavfilter -lavformat -lswscale -lavutil -lswresample -lavdevice
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

    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/lib/win/win64 -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer -lSeetaFaceTracker -lSeetaNet -lSeetaQualityAssessor
    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/lib/win/win64 -lopencv_world452
    # ******* Opencv *******

    # ******* Mqtt *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/QtMqtt/5.15.2/include
    LIBS += -L$$ROOT_DIR/3rd_party/QtMqtt/5.15.2/win/win64 -lQt5Mqtt
    # ******* Mqtt *******

}

macx {
    DEFINES += MAC_SPECIFIC_DEFINE

    # ******* Googletest *******
    GTEST_DIR = $$ROOT_DIR/3rd_party/GoogleTest

    INCLUDEPATH += $$GTEST_DIR/include/googletest
    LIBS += -L$$GTEST_DIR/lib/MacOS/arm64 -lgtest -lgtest_main

    message($$GTEST_DIR)
    # ******* Googletest *******

    # ******* VideoPlay *******
    # INCLUDEPATH += /usr/local/include/SDL2
    INCLUDEPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    DEPENDPATH += $$ROOT_DIR/3rd_party/FFmpeg/include

    # LIBS += -L/usr/local/lib/ -lSDL2
    LIBS += -L$$ROOT_DIR/3rd_party/FFmpeg/lib/MacOS/arm64 -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale
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

    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/lib/MacOS/arm64 -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer -lSeetaFaceTracker -lSeetaNet -lSeetaQualityAssessor
    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/lib/MacOS/arm64 -lopencv_world
    # ******* Opencv *******

    # ******* Mqtt *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/QtMqtt/6.5.3/include
    LIBS += -L$$ROOT_DIR/3rd_party/QtMqtt/6.5.3/MacOS/arm64 -lQtMqtt
    # ******* Mqtt *******

    # ******* Ice *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Ice-3.7.10_CXX11/include/generated
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Ice-3.7.10_CXX11/include
    LIBS += -L$$ROOT_DIR/3rd_party/Ice-3.7.10_CXX11/lib/MacOS/arm64 -lIce++11
    # ******* Ice *******


    # ******* RabbitMQ *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/RabbitMQ/include
    LIBS += -L/$$ROOT_DIR/3rd_party/RabbitMQ/lib/MacOS/arm64 -lrabbitmq.0.15.0
    # ******* RabbitMQ *******

    # ******* Protobuf *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Protobuf/include
    LIBS += -L$$ROOT_DIR/3rd_party/Protobuf/lib/MacOS/arm64 -lprotobuf
    # ******* Protobuf *******

    # ******* Redis *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Redis/include
    LIBS += -L$$ROOT_DIR/3rd_party/Redis/lib/MacOS/arm64 -lcpp_redis -ltacopie
    # ******* Redis *******

    # ******* Curl *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Curl/include
    LIBS += -L$$ROOT_DIR/3rd_party/Curl/lib/MacOS/arm64 -lcurl
    # ******* Curl *******

    # ******* JsonCpp *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/JsonCpp/include
    LIBS += -L$$ROOT_DIR/3rd_party/JsonCpp/lib/MacOS/arm64 -ljsoncpp
    # ******* JsonCpp *******

}

unix:!macx {

    # sudo apt install libva-dev libvdpau-dev
    # DEFINES += LINUX_SPECIFIC_DEFINE

    # ******* VideoPlay *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    DEPENDPATH += $$ROOT_DIR/3rd_party/FFmpeg/include
    LIBS += -L$$ROOT_DIR/3rd_party/FFmpeg/lib/Linux/amd64 -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lpostproc -lswresample -lswscale -lx264 -lfdk-aac
    # ******* VideoPlay *******

    # ******* hpdf *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/libhpdf/include
    LIBS += -L$$ROOT_DIR/3rd_party/libhpdf/Linux/amd64 -lhpdf
    # ******* hpdf *******

    # ******* Opencv *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceDetector/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceLandmarker/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceRecognizer/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/FaceTracker/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/QualityAssessor/include
    INCLUDEPATH += $$ROOT_DIR/3rd_party/Opencv/include/SeetaFace2/SeetaNet/include

    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/lib/Linux/amd64 -lSeetaFaceDetector -lSeetaFaceLandmarker -lSeetaFaceRecognizer -lSeetaFaceTracker -lSeetaNet -lSeetaQualityAssessor
    LIBS += -L$$ROOT_DIR/3rd_party/Opencv/lib/Linux/amd64 -lopencv_world
    # ******* Opencv *******

    # ******* Mqtt *******
    INCLUDEPATH += $$ROOT_DIR/3rd_party/QtMqtt/5.15.2/include
    LIBS += -L$$ROOT_DIR/3rd_party/QtMqtt/5.15.2/Linux/amd64 -lQt5Mqtt
    # ******* Mqtt *******
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
