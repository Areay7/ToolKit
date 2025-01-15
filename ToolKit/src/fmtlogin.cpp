#include "../include/fmtlogin.h"
#include "ui_fmtlogin.h"

#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    DatabaseManager *t = DatabaseManager::getInstance();

    QPixmap wxImage(":/res/LoginPage/wechat.png");
    ui->label_avatar->setAlignment(Qt::AlignCenter);
    ui->label_avatar->setPixmap(wxImage);

}

Widget::~Widget()
{
    DatabaseManager::destroyInstance();
    delete ui;
}
