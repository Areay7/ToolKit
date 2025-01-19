#include "fmtlogin.h"
#include <QApplication>

#ifdef Testgoogle
#include "gtest/gtest.h"
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);

#ifdef Testgoogle
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
#else
    FmtLogin w;
    w.show();
    return a.exec();
#endif
}
