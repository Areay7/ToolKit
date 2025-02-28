#ifndef FMTLOGIN_H
#define FMTLOGIN_H

#include <QWidget>
#include "databasemanager.h"
#include <mainpage.h>
#include <commondialog.h>

#include <opencv2/opencv.hpp>
// #include "qfaceobject.h"
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui {
class FmtLogin;
}
QT_END_NAMESPACE

enum class PageLogin : int
{
    Custom,
    Face,
    QRCode
};

class FmtLogin : public QWidget
{
    Q_OBJECT

public:
    FmtLogin(QWidget *parent = nullptr);
    ~FmtLogin();

public:
    void exitApp();
    bool myRegister();
    bool login();
    void timerEvent(QTimerEvent *event);

private:
    Ui::FmtLogin *ui;
    MainPage m_MainPage;
    CommonDialog m_box;

    DatabaseManager *t;

    cv::VideoCapture m_cap;
    cv::Mat m_image;
    int m_timerId;

private slots:
    void btnFaceClick();
    void btnQRCodeClick();
    void btnReturnClick();
};
#endif // FMTLOGIN_H
