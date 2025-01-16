#include "mainpage.h"
#include "ui_mainpage.h"
#include "commonutils.h"
#include "commonbase.h"
#include <QIcon>
#include <QList>
#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    // QPixmap chatImage(":/res/MainPage/chat_press.png");

    QPixmap boyImage(":/res/MainPage/boy.png");
    QPixmap scaledImage = boyImage.scaled(ui->label_avatar->width(), ui->label_avatar->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_avatar->setAlignment(Qt::AlignCenter);
    ui->label_avatar->setPixmap(scaledImage);

    QPixmap wxIcon(":/res/MainPage/wxBackGround.png");
    QPixmap iconScaledImage = wxIcon.scaled(ui->label_wxIcon->width(), ui->label_wxIcon->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_wxIcon->setAlignment(Qt::AlignCenter);
    ui->label_wxIcon->setPixmap(iconScaledImage);

    double a = add(4.5,3.2);
    qDebug() << "a : " << a;

    ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ChatPage));

    QList<QPushButton *> buttons = this->findChildren<QPushButton* >();
    for(QPushButton *btn : buttons)
    {
        connect(btn, &QPushButton::clicked, this, &MainPage::SwitchStatckPage);
    }



}

void MainPage::SwitchStatckPage()
{
    QObject *senderObj = sender();
    qDebug() << "Name ------------> " << senderObj->objectName();
    if(senderObj == ui->btn_chat)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ChatPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::ChatPage));
        CommonBase::logMessage(LogType::INFO, "btn_chat");
    }
    else if(senderObj == ui->btn_friend)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::FriendPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::FriendPage));
        CommonBase::logMessage(LogType::WARN, "btn_friend");
    }
    else if(senderObj == ui->btn_collect)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::CollectPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::CollectPage));
        CommonBase::logMessage(LogType::ERROR, "btn_collect");
    }
    else if(senderObj == ui->btn_moments)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::MomentsPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::MomentsPage));
        CommonBase::logMessage(LogType::DEBUG, "btn_moments");
    }
    else if(senderObj == ui->btn_tool)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ToolPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::ToolPage));
        CommonBase::logMessage(LogType::FATAL, "btn_tool");
    }

}

MainPage::~MainPage()
{
    delete ui;
}
