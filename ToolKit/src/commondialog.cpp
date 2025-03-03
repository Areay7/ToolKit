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

    connect(ui->P2_btn_ok, &QPushButton::clicked, this, &CommonDialog::clickOk);
    connect(ui->P3_btn_ok, &QPushButton::clicked, this, &CommonDialog::clickOk);
    connect(ui->P3_btn_cancel, &QPushButton::clicked, this, &CommonDialog::clickCancel);
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
    else if(2 == btnNum)
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

void CommonDialog::clickOk()
{
    qDebug() << "click ok !";
    accept();
}

void CommonDialog::clickCancel()
{
    qDebug() << "click  cancel !";
    reject();
}



Cartoon::Cartoon(QObject *parent)
{

}

Cartoon::~Cartoon()
{

}

void Cartoon::playWeChatSound() {
    QSoundEffect* sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(":/res/LoginPage/scan_note.wav"));
    sound->setVolume(0.8);

    // 播放完成后自动释放内存
    QObject::connect(sound, &QSoundEffect::playingChanged, [sound]() {
        if (!sound->isPlaying()) {
            sound->deleteLater();
        }
    });

    sound->play();
}
