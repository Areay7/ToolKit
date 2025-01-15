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
    $$PWD/src/commondialog.cpp

HEADERS += \
    $$PWD/include/databasemanager.h \
    $$PWD/include/fmtlogin.h \
    $$PWD/include/mainpage.h \
    $$PWD/include/commondialog.h

FORMS += \
    $$PWD/ui/fmtlogin.ui \
    $$PWD/ui/mainpage.ui \
    $$PWD/ui/commondialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 将路径作为宏定义传递给编译后的可执行文件
DEFINES += PRO_FILE_PWD=\\\"$$PWD\\\"

RESOURCES += \
    res.qrc
