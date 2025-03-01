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


    m_timer.setInterval(3000);

    // connect
    connect(ui->btn_exit, &QPushButton::clicked, this, &FmtLogin::exitApp);
    connect(ui->btn_register, &QPushButton::clicked, this, &FmtLogin::myRegister);
    connect(ui->btn_login, &QPushButton::clicked, this, &FmtLogin::login);
    connect(ui->btn_face, &QPushButton::clicked, this, &FmtLogin::btnFaceClick);
    connect(ui->btn_QRCode, &QPushButton::clicked, this, &FmtLogin::btnQRCodeClick);
    connect(ui->btn_return, &QPushButton::clicked, this, &FmtLogin::btnReturnClick);
    connect(ui->btn_return_2, &QPushButton::clicked, this, &FmtLogin::btnReturnClick);
    connect(&m_timer, &QTimer::timeout, this, &FmtLogin::checkLoginStatus);
    connect(this, &FmtLogin::loginSuccess, this, &FmtLogin::loginSuccessSlot);
    connect(ui->btn_faceCheck, &QPushButton::clicked, this, &FmtLogin::btnCheckFaceClick);
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
        loginSuccessSlot();
    }
    else
    {
        m_box.setButtonWindow("登陆失败，\n 账号或密码错误", 1);
    }
    return res;
}

void FmtLogin::loginSuccessSlot()
{
    m_MainPage.show();
    stopChecking();
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
    startChecking();

    QPixmap boyImage(":/res/LoginPage/QRCode.png");
    QPixmap scaledImage = boyImage.scaled(ui->label_QRCode->width(), ui->label_QRCode->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_QRCode->setAlignment(Qt::AlignCenter);
    ui->label_QRCode->setPixmap(scaledImage);
    qDebug() << "-----------------> " << __FUNCTION__ << "<----------------- 2";
    // qDebug() << scaledImage;
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

void FmtLogin::btnCheckFaceClick()
{
    QString proFilePath = QString(PRO_FILE_PWD);
    QString imageFile = QString(proFilePath + "/data/%1.jpg").arg((QString("Areay7").toUtf8().toBase64()));
    cv::imwrite(imageFile.toUtf8().data(), m_image);

    killTimer(m_timerId);
    m_cap.release();
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

void FmtLogin::checkLoginStatus() {
    QUrl url(LOGIN_URL);
    QNetworkRequest request(url);

    // 设置通用请求头
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "application/json");

    QNetworkReply* reply = m_networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleNetworkReply(reply);
    });
}

void FmtLogin::handleNetworkReply(QNetworkReply *reply) {
    qDebug() << "-----------------> " << __FUNCTION__ << "<----------------- 3";
    reply->deleteLater(); // 确保内存释放

    if (reply->error() != QNetworkReply::NoError) {
        emit networkError(reply->errorString());
        return;
    }

    const QByteArray response = reply->readAll();
    const QString responseStr = QString::fromUtf8(response).trimmed();

    if (responseStr.compare("ok", Qt::CaseInsensitive) == 0) {
        qDebug() << "----------------compare ok------------------------";
        emit loginSuccess();
    }
    else if (responseStr.compare("no", Qt::CaseInsensitive) == 0) {
        qDebug() << "----------------compare no------------------------";
        emit loginPending();
    }
    else {
        emit networkError("Unknown server response: " + responseStr);
    }
}

void FmtLogin::startChecking() {
    m_timer.start();
}

void FmtLogin::stopChecking() {
    m_timer.stop();
}
