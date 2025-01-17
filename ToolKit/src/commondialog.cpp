#include "commondialog.h"
#include "ui_commondialog.h"

#include <QDebug>

CommonDialog::CommonDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CommonDialog)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->progressBar->setValue(0);

    connect(ui->P2_btn_ok, &QPushButton::clicked, this, &CommonDialog::click_ok);
    connect(ui->P3_btn_ok, &QPushButton::clicked, this, &CommonDialog::click_ok);
    connect(ui->P3_btn_cancel, &QPushButton::clicked, this, &CommonDialog::click_cancel);
}

CommonDialog::~CommonDialog()
{
    delete ui;
}

int CommonDialog::setButtonWindow(QString msg, int btnNum, const QString &btnText_1, const QString &btnText_2, bool is_exec)
{
    ui->stackedWidget->setCurrentIndex(btnNum);

    if(1 == btnNum)
    {
        ui->P2_btn_ok->setText(btnText_1);
        ui->P2_label_msg->setText(msg);
    }
    else if(2==btnNum)
    {
        ui->P3_btn_ok->setText(btnText_2);
        ui->P3_btn_cancel->setText(btnText_1);
        ui->P3_label_msg->setText(msg);
    }
    if(is_exec)
    {
        return exec();
    }
}

void CommonDialog::setBarValue(int value)
{

}

void CommonDialog::click_ok()
{
    qDebug() << "click ok !";
    accept();
}

void CommonDialog::click_cancel()
{
    qDebug() << "click  cancel !";
    reject();
}


