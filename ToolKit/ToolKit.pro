QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# QMAKE_CXXFLAGS += -fsanitize=address
# QMAKE_LFLAGS += -fsanitize=address

#DEFINES += Testgoogle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

ROOT_DIR = $$PWD

include($$ROOT_DIR/3rd_party/lib.pri)
include($$ROOT_DIR/3rd_party/QXlsx/QXlsx.pri)             # QXlsx源代码，版本V1.4.3  https://github.com/QtExcel/QXlsx/releases
INCLUDEPATH += ROOT_DIR/3rd_party/QXlsx


# INCLUDEPATH += $$ROOT_DIR
INCLUDEPATH += $$ROOT_DIR/include
INCLUDEPATH += $$ROOT_DIR/include/VideoPlay
INCLUDEPATH += $$ROOT_DIR/include/Xlsx
INCLUDEPATH += $$ROOT_DIR/include/PDF
INCLUDEPATH += $$ROOT_DIR/include/OpencvServer

SOURCES += \
    $$ROOT_DIR/src/databasemanager.cpp \
    $$ROOT_DIR/src/fmtlogin.cpp \
    $$ROOT_DIR/src/main.cpp \
    $$ROOT_DIR/src/mainpage.cpp \
    $$ROOT_DIR/src/commondialog.cpp \
    $$ROOT_DIR/src/msgrecord.cpp \
    $$ROOT_DIR/src/commonutils.cpp \
    $$ROOT_DIR/src/commonbase.cpp \
    src/OpencvServer/opencvWindow.cpp \
    src/OpencvServer/qfaceobject.cpp \
    src/OpencvServer/registerwin.cpp \
    src/OpencvServer/selectwin.cpp


HEADERS += \
    $$ROOT_DIR/include/databasemanager.h \
    $$ROOT_DIR/include/fmtlogin.h \
    $$ROOT_DIR/include/mainpage.h \
    $$ROOT_DIR/include/commondialog.h \
    $$ROOT_DIR/include/msgrecord.h \
    $$ROOT_DIR/include/commonutils.h \
    $$ROOT_DIR/include/commonbase.h \
    include/OpencvServer/opencvWindow.h \
    include/OpencvServer/qfaceobject.h \
    include/OpencvServer/registerwin.h \
    include/OpencvServer/selectwin.h


FORMS += \
    $$ROOT_DIR/ui/fmtlogin.ui \
    $$ROOT_DIR/ui/mainpage.ui \
    $$ROOT_DIR/ui/commondialog.ui \
    $$ROOT_DIR/ui/MsgRecord.ui \
    $$ROOT_DIR/ui/msgrecord.ui

# 使用通配符引入 include/VideoPlay 目录下的所有 .h 文件
Video_HEADERS = $$files($$ROOT_DIR/include/VideoPlay/*.h)
message($$Video_HEADERS)
HEADERS += $$Video_HEADERS
HEADERS = $$unique(HEADERS)

# 使用通配符引入 include/VideoPlay 目录下的所有 .cpp 文件
Video_SOURCES = $$files($$ROOT_DIR/src/VideoPlay/*.cpp)
message($$Video_SOURCES)
SOURCES += $$Video_SOURCES
SOURCES = $$unique(SOURCES)

Xlsx_HEADERS = $$files($$ROOT_DIR/include/Xlsx/*.h)
message($$Xlsx_HEADERS)
HEADERS += $$Xlsx_HEADERS
HEADERS = $$unique(HEADERS)

# 使用通配符引入 include/VideoPlay 目录下的所有 .cpp 文件
Xlsx_SOURCES = $$files($$ROOT_DIR/src/Xlsx/*.cpp)
message($$Xlsx_SOURCES)
SOURCES += $$Xlsx_SOURCES
SOURCES = $$unique(SOURCES)

PDF_HEADERS = $$files($$ROOT_DIR/include/PDF/*.h)
message($$PDF_HEADERS)
HEADERS += $$PDF_HEADERS
HEADERS = $$unique(HEADERS)

# 使用通配符引入 include/VideoPlay 目录下的所有 .cpp 文件
PDF_SOURCES = $$files($$ROOT_DIR/src/PDF/*.cpp)
message($$PDF_SOURCES)
SOURCES += $$PDF_SOURCES
SOURCES = $$unique(SOURCES)

Test_SOURCES = $$files($$ROOT_DIR/test/*.cpp)
message($$Test_SOURCES)
SOURCES += $$Test_SOURCES
SOURCES = $$unique(SOURCES)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 将路径作为宏定义传递给编译后的可执行文件
DEFINES += PRO_FILE_PWD=\\\"$$ROOT_DIR\\\"

RESOURCES += \
    res.qrc
