#include "fmtlogin.h"
#include "ui_fmtlogin.h"

#include <QPixmap>
#include <QTimer>

FmtLogin::FmtLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FmtLogin)
{
    ui->setupUi(this);
    // setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->stackedWidget->setCurrentIndex(static_cast<int>(PageLogin::Custom));

    t = DatabaseManager::getInstance();

    m_MainPage.hide();

    QPixmap wxImage(":/res/LoginPage/wechat.png");
    ui->label_avatar->setAlignment(Qt::AlignCenter);
    ui->label_avatar->setPixmap(wxImage);

    // connect
    connect(ui->btn_exit, &QPushButton::clicked, this, &FmtLogin::exitApp);
    connect(ui->btn_register, &QPushButton::clicked, this, &FmtLogin::myRegister);
    connect(ui->btn_login, &QPushButton::clicked, this, &FmtLogin::login);
    connect(ui->btn_face, &QPushButton::clicked, this, &FmtLogin::btnFaceClick);
    connect(ui->btn_QRCode, &QPushButton::clicked, this, &FmtLogin::btnQRCodeClick);
    connect(ui->btn_return, &QPushButton::clicked, this, &FmtLogin::btnReturnClick);
    connect(ui->btn_return_2, &QPushButton::clicked, this, &FmtLogin::btnReturnClick);
}

FmtLogin::~FmtLogin()
{
    DatabaseManager::destroyInstance();
    delete ui;
}

void FmtLogin::exitApp()
{
    QApplication::quit();
}

bool FmtLogin::myRegister()
{
    QString name = "AAA";
    QString userAccount = ui->lineEdit_user->text();
    QString userPassword = ui->lineEdit_password->text();
    bool res = t->InsertUser(name , userAccount, userPassword);
    return res;
}

bool FmtLogin::login()
{
    QString name = "AAA";
    QString userAccount = ui->lineEdit_user->text();
    QString userPassword = ui->lineEdit_password->text();
    bool res = t->Login(name, userAccount, userPassword);
    if(!res)
    {
        this->hide();
        m_MainPage.show();
    }
    else
    {
        m_box.setButtonWindow("登陆失败，\n 账号或密码错误", 1);
    }
    return res;
}

void FmtLogin::btnFaceClick()
{
    if(m_cap.open(0))
    {
        qDebug() << "cap true -------------";
        m_timerId = startTimer(100);

    }
    else
    {
        qDebug() << "cap false -------------";
        killTimer(m_timerId);
        m_cap.release();
    }
    ui->stackedWidget->setCurrentIndex(static_cast<int>(PageLogin::Face));
}

void FmtLogin::btnQRCodeClick()
{
    qDebug() << "-----------------> " << __FUNCTION__ << "<----------------- 1";

    QPixmap boyImage(":/res/LoginPage/QRCode.jpg");
    QPixmap scaledImage = boyImage.scaled(ui->label_QRCode->width(), ui->label_QRCode->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_QRCode->setAlignment(Qt::AlignCenter);
    ui->label_QRCode->setPixmap(scaledImage);
    qDebug() << "-----------------> " << __FUNCTION__ << "<----------------- 2";
    qDebug() << scaledImage;
    ui->stackedWidget->setCurrentIndex(static_cast<int>(PageLogin::QRCode));
}

void FmtLogin::btnReturnClick()
{
    if(m_cap.isOpened())
    {
        m_cap.release();
    }
    ui->stackedWidget->setCurrentIndex(static_cast<int>(PageLogin::Custom));
}

void FmtLogin::timerEvent(QTimerEvent *event)
{
    // 获取摄像头数据并且显示在界面
    if(m_cap.isOpened())
    {
        m_cap >> m_image;
        if(m_image.data == nullptr) return;
    }

    // Mat -> QImage
    cv::Mat rgbImage;
    cv::cvtColor(m_image, rgbImage, cv::COLOR_BGR2RGB);
    QImage qImg(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step1(), QImage::Format_RGB888);

    // 在 QT 界面上显示
    QPixmap mmp = QPixmap::fromImage(qImg);
    mmp = mmp.scaledToWidth(ui->label_Face->width());
    ui->label_Face->setPixmap(mmp);
}
