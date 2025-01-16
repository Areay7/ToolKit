QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/src/databasemanager.cpp \
    $$PWD/src/fmtlogin.cpp \
    $$PWD/src/main.cpp \
    $$PWD/src/mainpage.cpp \
    $$PWD/src/commondialog.cpp \
    $$PWD/src/msgrecord.cpp \
    $$PWD/src/commonutils.cpp \
    $$PWD/src/commonbase.cpp

HEADERS += \
    $$PWD/include/databasemanager.h \
    $$PWD/include/fmtlogin.h \
    $$PWD/include/mainpage.h \
    $$PWD/include/commondialog.h \
    $$PWD/include/msgrecord.h \
    $$PWD/include/commonutils.h \
    $$PWD/include/commonbase.h

FORMS += \
    $$PWD/ui/fmtlogin.ui \
    $$PWD/ui/mainpage.ui \
    $$PWD/ui/commondialog.ui \
    $$PWD/ui/MsgRecord.ui \
    $$PWD/ui/msgrecord.ui

# 区分操作系统
win32 {
    # LIBS += -LC:/path/to/windows/libs -lmywindowslib
    # INCLUDEPATH += C:/path/to/windows/includes
    # DEFINES += WINDOWS_SPECIFIC_DEFINE
}

macx {
    # LIBS += -L/Users/username/path/to/mac/libs -lmymaclib
    # INCLUDEPATH += /Users/username/path/to/mac/includes
    # DEFINES += MAC_SPECIFIC_DEFINE
}

unix:!macx {
    # LIBS += -L/usr/local/path/to/linux/libs -lmylinuxlib
    # INCLUDEPATH += /usr/local/path/to/linux/includes
    # DEFINES += LINUX_SPECIFIC_DEFINE
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 将路径作为宏定义传递给编译后的可执行文件
DEFINES += PRO_FILE_PWD=\\\"$$PWD\\\"

RESOURCES += \
    res.qrc
