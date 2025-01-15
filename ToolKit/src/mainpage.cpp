#include "mainpage.h"
#include "ui_mainpage.h"

#include <QIcon>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    QPixmap chatImage(":/res/MainPage/chat_press.png");



}

MainPage::~MainPage()
{
    delete ui;
}
