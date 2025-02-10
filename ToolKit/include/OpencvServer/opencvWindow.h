#if 0

#ifndef OPENCVWINDOW_H
#define OPENCVWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDateTime>
#include <QThread>
#include <QSqlQuery>
#include <QSqlError>

#include "qfaceobject.h"

#include <QMainWindow>
#include <QContextMenuEvent>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui {
class OpencvWindow;
}
QT_END_NAMESPACE

class OpencvWindow : public QMainWindow
{
    Q_OBJECT

public:
    OpencvWindow(QWidget *parent = nullptr);

    ~OpencvWindow();

private slots:
    void accept_client();
    void read_data();
    void recv_faceid(int64_t faceid);

signals:
    void query(Mat& image);

private:
    Ui::OpencvWindow *ui;
    QTcpServer mserver;
    QTcpSocket *msocket;
    quint64 bsize;

    QFaceObject fobj;

    QSqlTableModel model;

private:
    QMenu *mExitMenu;   // 右键退出的菜单
    QAction *mExitAct;  // 退出行为 - 菜单项
    QAction *mReturnAct; // 返回行为 - 菜单项
protected:
    // 重写父类方法
    void contextMenuEvent(QContextMenuEvent *event);

};
#endif // OPENCVWINDOW_H

#endif
