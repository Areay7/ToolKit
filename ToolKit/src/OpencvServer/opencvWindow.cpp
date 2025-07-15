#if 0

#include "opencvWindow.h"

OpencvWindow::OpencvWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OpencvWindow)
{
    ui->setupUi(this);

    // 监听，启动服务器  当有新客户端连接会发送 newconnection 信号
    mserver.listen(QHostAddress::Any, 9999);
    connect(&mserver, &QTcpServer::newConnection, this, &OpencvWindow::accept_client);

    bsize = 0;

    // 给 sql 模型绑定表格
    model.setTable("employee");

    // 创建一个线程
    QThread *thread = new QThread();
    // 把 QFaceObject 对象移动到线程中执行
    fobj.moveToThread(thread);
    // 启动线程
    thread->start();

    connect(this, &OpencvWindow::query, &fobj, &QFaceObject::face_query);
    // 关联 QFaceObject 对象里面的 send_faceid 信号
    connect(&fobj, &QFaceObject::send_faceid, this, &OpencvWindow::recv_faceid);


    // 构建右键菜单
    mExitMenu  = new QMenu(this);
    mExitAct = new QAction();
    mReturnAct = new QAction();

    mExitAct->setText("退出");
    mExitAct->setIcon(QIcon(":/res/close.png"));
    mReturnAct->setText("返回菜单"); // 添加返回动作文本
    mReturnAct->setIcon(QIcon(":/res/close.png")); // 添加返回动作图标

    // 将动作添加到右键菜单
    mExitMenu->addAction(mExitAct);
    mExitMenu->addAction(mReturnAct); // 将返回动作添加到右键菜单

    // 连接返回动作的信号和槽
    connect(mExitAct, &QAction::triggered, this, [=]{
        qApp->exit(0);
    });

    connect(mReturnAct, &QAction::triggered, this, [=]{
        // 隐藏当前窗口（即 MainWindow）
        hide();
        // 显示主窗口（即 MainWidget）
        parentWidget()->show();
    });
}

OpencvWindow::~OpencvWindow()
{
    delete ui;
}

void OpencvWindow::accept_client()
{
    // 获取通信套接字
    msocket = mserver.nextPendingConnection();

    // 当客户端有数据到达，会发送 readyRead 信号
    connect(msocket, &QTcpSocket::readyRead, this, &OpencvWindow::read_data);

}

void OpencvWindow::read_data()
{
    // 把套接字绑定到数据流
    QDataStream stream(msocket);
    stream.setVersion(QDataStream::Qt_5_14);

    if(bsize == 0)
    {
        if(msocket->bytesAvailable() < (qint64)sizeof(bsize)) return;

        // 采集数据长度
        stream >> bsize;
    }

        // 数据还没发送完成，返回继续等待
    if(msocket->bytesAvailable() < bsize)
    {
        // qDebug() << "bsize 1 : " << bsize;
        return;
    }

    QByteArray data;
    stream >> data;
    bsize = 0;
    // 没有读取到数据
    if(data.size() == 0)
    {
        return;
    }

    // qDebug() << "bsize 2 : " << bsize;

    // 显示图片
    QPixmap mmp;
    mmp.loadFromData(data, "jpg");
    mmp = mmp.scaled(ui->picLb->size());
    ui->picLb->setPixmap(mmp);

    // 识别人脸
    Mat faceImage;
    std::vector<uchar> decode;
    decode.resize(data.size());
    memcpy(decode.data(), data.data(), data.size());

    faceImage = imdecode(decode, IMREAD_COLOR);

    // int faceid = fobj.face_query(faceImage);
    emit query(faceImage);
}

void OpencvWindow::recv_faceid(int64_t faceid)
{
    qDebug() << "识别到的 faceid : " << faceid;

    // 从数据库中查询 faceid
    // 给模型设置过滤器

    if(faceid < 0)
    {
        QString sdmsg = "{\"EmployeeID\":\"\", \"name\":\"\", \"department\":\"\", \"time\":\"\"}";
        // 把打包好的数据发送给客户端
        msocket->write(sdmsg.toUtf8());
        return;
    }

    model.setFilter(QString("FaceID=%1").arg(faceid));
    // 查询
    model.select();
    // 判断是否查询到数据
    if(model.rowCount() == 1)
    {
        // 学号，姓名，部门，时间
        // {EmployeeID:%1, name:%2, department:物联网工程, time:%3}
        QSqlRecord record = model.record(0);
        QString sdmsg = QString("{\"EmployeeID\":\"%1\", \"name\":\"%2\", \"department\":\"物联网工程\", \"time\":\"%3\"}")
                            .arg(record.value("EmployeeID").toString()).arg(record.value("name").toString())
                            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        // 把数据写入数据库 - 考勤表
        QString insertSql = QString("insert into attendance(EmployeeID) value('%1')").arg(record.value("EmployeeID").toString());
        QSqlQuery query;
        if(!query.exec(insertSql))
        {
            QString sdmsg = "{\"EmployeeID\":\"\", \"name\":\"\", \"department\":\"\", \"time\":\"\"}";
            // 把打包好的数据发送给客户端
            msocket->write(sdmsg.toUtf8());
            qDebug() << "query error : " << query.lastError().text();
            return;
        }
        else
        {
            // 把打包好的数据发送给客户端
            msocket->write(sdmsg.toUtf8());
        }
    }
}

// 重写父类虚函数
// 父类中默认的实现  是忽略右键菜单事件
// 重写之后，就可以处理右键菜单
void OpencvWindow::contextMenuEvent(QContextMenuEvent *event)
{
    // 弹出右键菜单
    mExitMenu->exec(QCursor::pos());

    event->accept();
}

#endif
