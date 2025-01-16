#include "mainpage.h"
#include "ui_mainpage.h"
#include <QIcon>


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



    msg.show();

}

MainPage::~MainPage()
{
    delete ui;
}
