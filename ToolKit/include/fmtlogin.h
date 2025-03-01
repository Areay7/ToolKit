#ifndef FMTLOGIN_H
#define FMTLOGIN_H

#include <QWidget>
#include <mainpage.h>
#include <commondialog.h>
#include <QNetworkAccessManager>
#include <QTimer>
#include <opencv2/opencv.hpp>
// #include "qfaceobject.h"
#include <QDebug>

#include "databasemanager.h"

#define LOGIN_URL "http://114.115.148.19:443/login"

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
    void checkLoginStatus();
    void handleNetworkReply(QNetworkReply* reply);
    void startChecking();
    void stopChecking();
    void loginSuccessSlot();

private:
    Ui::FmtLogin *ui;
    MainPage m_MainPage;
    CommonDialog m_box;

    DatabaseManager *t;

    cv::VideoCapture m_cap;
    cv::Mat m_image;
    int m_timerId;

    QTimer m_timer;
    QNetworkAccessManager m_networkManager;

signals:
    void loginSuccess();    // 登录成功信号
    void loginPending();    // 等待登录信号
    void networkError(const QString& error); // 网络错误信号

private slots:
    void btnFaceClick();
    void btnQRCodeClick();
    void btnReturnClick();
    void btnCheckFaceClick();
};
#endif // FMTLOGIN_H
