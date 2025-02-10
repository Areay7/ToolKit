#if 0

#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>
#include <QFileDialog>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <opencv2/opencv.hpp>

#include <QDebug>
#include "qfaceobject.h"

using namespace cv;


namespace Ui {
class RegisterWin;
}

class RegisterWin : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWin(QWidget *parent = nullptr);
    ~RegisterWin();

    void timerEvent(QTimerEvent *event);

private slots:
    void on_resetBtn_clicked();

    void on_addPicBtn_clicked();

    void on_registerBtn_clicked();

    void on_videoSwitchBtn_clicked();

    void on_cameraBtn_clicked();

private:
    Ui::RegisterWin *ui;
    int timerid;

    VideoCapture cap;
    Mat image;
};

#endif // REGISTERWIN_H

#endif
