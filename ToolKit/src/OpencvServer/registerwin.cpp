#if 0

#include "registerwin.h"
#include "ui_registerwin.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

RegisterWin::RegisterWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWin)
{
    ui->setupUi(this);
}

RegisterWin::~RegisterWin()
{
    delete ui;
}

void RegisterWin::timerEvent(QTimerEvent *event)
{
    // 获取摄像头数据并且显示在界面
    if(cap.isOpened())
    {
        cap >> image;
        if(image.data == nullptr) return;
    }

    // Mat -> QImage
    Mat rgbImage;
    cvtColor(image, rgbImage, COLOR_BGR2RGB);
    QImage qImg(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step1(), QImage::Format_RGB888);

    // 在 QT 界面上显示
    QPixmap mmp = QPixmap::fromImage(qImg);
    mmp = mmp.scaledToWidth(ui->headPicLb->width());
    ui->headPicLb->setPixmap(mmp);
}

void RegisterWin::on_resetBtn_clicked()
{
    // 清空数据
    ui->nameEdit->clear();
    ui->birthdayEdit->setDate(QDate::currentDate());
    ui->addressEdit->clear();
    ui->phoneEdit->clear();
    ui->picFileEdit->clear();
}

void RegisterWin::on_addPicBtn_clicked()
{
    // 通过文件对话框，选中图片路径
    QString filePath =  QFileDialog::getOpenFileName(this);
    ui->picFileEdit->setText(filePath);

    // 显示图片
    QPixmap mmp(filePath);
    mmp = mmp.scaledToWidth(ui->headPicLb->width());
    ui->headPicLb->setPixmap(mmp);

    // 识别人脸

}

void RegisterWin::on_registerBtn_clicked()
{
    // 1. 通过照片，结合 faceObject 模块得到 faceID
    QFaceObject faceObj;
    QString filePath = ui->picFileEdit->text();
    std::cout << "Reading image from path: " << filePath.toStdString() << std::endl;

    Mat image = imread(filePath.toUtf8().data());
    if (image.empty()) {
        std::cerr << "Failed to read image: " << filePath.toStdString() << std::endl;
        QMessageBox::critical(this, "Error", "Failed to read image. Please check the file path and try again.");
        return;
    }

    int faceID = faceObj.face_register(image);
    qDebug() << "faceID : " <<faceID;

    // 把头像保存到一个规定路径
    QString headFile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    imwrite(headFile.toUtf8().data(), image);

    // 2. 把个人数据存到数据库 employee
    QSqlTableModel model;
    // 设置表名
    model.setTable("employee");

    QSqlRecord record = model.record();
    // 设置数据
    record.setValue("name", ui->nameEdit->text());
    record.setValue("sex", ui->mrb->isChecked() ? "男" : "女");
    record.setValue("birthday", ui->birthdayEdit->text());
    record.setValue("address", ui->addressEdit->text());
    record.setValue("phone", ui->phoneEdit->text());
    record.setValue("FaceID", faceID);
    // 头像路径
    record.setValue("headFile", headFile);

    // 把记录插入到数据库中
    bool ret = model.insertRecord(0, record);

    // 3. 提示注册成功
    if(ret)
    {
        QMessageBox::information(this, "注册提示", "注册成功");
        // 提交
        model.submit();
    }
    else
    {
        QMessageBox::information(this, "注册提示", "注册失败");
    }
}

void RegisterWin::on_videoSwitchBtn_clicked()
{
    if(ui->videoSwitchBtn->text() == "打开摄像头")
    {
        // 打开摄像头
        if(cap.open(0))
        {
            ui->videoSwitchBtn->setText("关闭摄像头");
            // 启动定时器事件
            timerid = startTimer(100);
        }
    }
    else
    {
        // 关闭定时器事件
        killTimer(timerid);
        ui->videoSwitchBtn->setText("打开摄像头");

        // 关闭摄像头
        cap.release();
    }
}

void RegisterWin::on_cameraBtn_clicked()
{
    // 保存数据
    // 把头像保存到一个规定路径
    QString headFile = QString("./data/%1.jpg").arg(QString(ui->nameEdit->text().toUtf8().toBase64()));
    ui->picFileEdit->setText(headFile);
    imwrite(headFile.toUtf8().data(), image);

    // 关闭定时器事件
    killTimer(timerid);
    ui->videoSwitchBtn->setText("打开摄像头");

    // 关闭摄像头
    cap.release();
}

#endif
