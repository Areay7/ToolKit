#include "fmtlogin.h"
#include "ui_fmtlogin.h"

#include <QPixmap>

FmtLogin::FmtLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FmtLogin)
{
    ui->setupUi(this);
    // setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);

    t = DatabaseManager::getInstance();

    m_MainPage.hide();

    QPixmap wxImage(":/res/LoginPage/wechat.png");
    ui->label_avatar->setAlignment(Qt::AlignCenter);
    ui->label_avatar->setPixmap(wxImage);

    // connect
    connect(ui->btn_exit, &QPushButton::clicked, this, &FmtLogin::exitApp);
    connect(ui->btn_register, &QPushButton::clicked, this, &FmtLogin::myRegister);
    connect(ui->btn_login, &QPushButton::clicked, this, &FmtLogin::login);

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


