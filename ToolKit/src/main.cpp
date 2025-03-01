#include "fmtlogin.h"
#include <QApplication>
#include <QIcon>
#include <QTextCodec>

#ifdef Testgoogle
#include "gtest/gtest.h"
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    QIcon icon(":/res/MainPage/wxicon_32_32.ico");


#ifdef Testgoogle
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
#else


    FmtLogin w;
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
#endif
}
