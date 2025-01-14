#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    DatabaseManager *t = DatabaseManager::getInstance();


}

Widget::~Widget()
{
    DatabaseManager::destroyInstance();
    delete ui;
}
