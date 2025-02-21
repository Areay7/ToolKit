#include "mainpage.h"
#include "ui_mainpage.h"

#include <QIcon>
#include <QList>
#include <QScrollBar>
#include <QFileDialog>
#include <QStyle>
#include <QRegExp>
// #include <QRegularExpression>
// #include <QRegularExpressionMatch>
#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
    , m_isPlay(false)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    setPicture();

    double a = add(4.5,3.2);
    qDebug() << "a : " << a;

    ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ChatPage));
    ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::ChatPage));

    QList<QPushButton *> buttons = this->findChildren<QPushButton* >();
    for(QPushButton *btn : buttons)
    {
        connect(btn, &QPushButton::clicked, this, &MainPage::switchStatckPage);
    }

    m_lastSelectedWidget = new MsgRecord();

    m_scrollArea = new QScrollArea(ui->widget_verticalLayout);
    m_scrollArea->setWidgetResizable(true);

    // 隐藏滚动条但保留功能
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_containerWidget = new QWidget(m_scrollArea);
    m_containerLayout = new QVBoxLayout(m_containerWidget);

    m_scrollArea->setWidget(m_containerWidget);
    ui->verticalLayout->addWidget(m_scrollArea);



    for(int i = 0; i < 10; ++i)
    {
        // 使用 std::shared_ptr 管理 MsgRecord 对象
        std::shared_ptr<MsgRecord> msgRecord = std::make_shared<MsgRecord>();

        // 将 shared_ptr 添加到 m_widgetList
        m_widgetList.append(msgRecord);

        // 将 msgRecord 作为原始指针传递给 m_containerLayout
        m_containerLayout->addWidget(msgRecord.get()); // 使用 get() 获取裸指针

        // 连接信号与槽
        connect(msgRecord.get(), &MsgRecord::clicked, this, &MainPage::onWidgetClicked);
    }

    updateVisibleWidgets();


    // NEW
    m_readThread = std::make_shared<ReadThread>();
    m_xlsx = std::make_shared<XlsxManager>();
    m_commonUtils = std::make_shared<CommonUtils>();

    connect(m_readThread.get(), &ReadThread::updateImage, ui->widget_VideoPlay, &PlayImage::updateImage, Qt::QueuedConnection);
    connect(m_readThread.get(), &ReadThread::playState, this, &MainPage::on_playState, Qt::QueuedConnection);
    connect(m_commonUtils.get(), &CommonUtils::sendMsg, this, &MainPage::recvMsg, Qt::DirectConnection);

}


void MainPage::switchStatckPage()
{
    QObject *senderObj = sender();
    qDebug() << "Name ------------> " << senderObj->objectName();
    if(senderObj == ui->btn_chat)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ChatPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::ChatPage));
        CommonBase::logMessage(LogType::INFO, "btn_chat");
    }
    else if(senderObj == ui->btn_friend)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::FriendPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::FriendPage));
        CommonBase::logMessage(LogType::WARN, "btn_friend");

        m_commonUtils->sendRequest("你是一名资深的C++程序员", "如何高效学习Linux C++ QT，并且快速适应工作要求");


        CommonBase::getCpuUse();
        CommonBase::getMemoryUse();
    }
    else if(senderObj == ui->btn_collect)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::CollectPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::CollectPage));
        CommonBase::logMessage(LogType::ERROR, "btn_collect");
    }
    else if(senderObj == ui->btn_moments)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::MomentsPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::MomentsPage));
        CommonBase::logMessage(LogType::DEBUG, "btn_moments");
    }
    else if(senderObj == ui->btn_tool)
    {
        ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ToolPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::ToolPage));
        CommonBase::logMessage(LogType::FATAL, "btn_tool");
    }
    else if(senderObj == ui->btn_excel)
    {
        bool ret = m_xlsx->openOffice();
        if(ret)
            CommonBase::logMessage(LogType::INFO, "open success");
        else
            CommonBase::logMessage(LogType::FATAL, "open fail");
    }
    else if(senderObj == ui->btn_videoPlay_Play)
    {
        openClick();
    }
    else if(senderObj == ui->btn_videoPlay_Stop)
    {
        pauseClick();
    }
    else if(senderObj == ui->btn_videoPlay_select)
    {
        selectFileToPlay();
    }
    else if(senderObj == ui->btn_videoPlay)
    {
        // ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ToolPage));
        ui->stackedWidget_main->setCurrentIndex(static_cast<int>(StackPage::VideoPlayPage));
    }
    else if(senderObj == ui->btn_videoPlay_exit)
    {
        free();
        exitApp();
    }



}

void MainPage::onWidgetClicked(MsgRecord *msgRecord)
{
    if(m_lastSelectedWidget)
    {
        m_lastSelectedWidget->setSelected(false); // 恢复上一个选中的控件样式
    }

    msgRecord->setSelected(true);
    m_lastSelectedWidget = msgRecord;
}

void MainPage::selectFileToPlay()
{
    QString strName = QFileDialog::getOpenFileName(this, "选择播放视频~！", "/", "视频 (*.mp4 *.m4v *.mov *.avi *.flv);; 其它(*)");
    qDebug() << "strName -----> " << strName;
    if(strName.isEmpty())
    {
        qDebug() << "strName is Empty !";
        return;
    }
    ui->comboBox_url->addItem(strName);
    ui->comboBox_url->setCurrentText(strName);
}

void MainPage::openClick()
{
    if(ui->btn_videoPlay_Play->styleSheet().contains("open.png"))
    {
        m_readThread->open(ui->comboBox_url->currentText());
        ui->btn_videoPlay_Play->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/pause.png);}");
    }
    else if (ui->btn_videoPlay_Play->styleSheet().contains("pause.png"))
    {
        m_readThread->pause(true);
        ui->btn_videoPlay_Play->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/play.png);}");
    }
    else if (ui->btn_videoPlay_Play->styleSheet().contains("play.png"))
    {
        m_readThread->pause(false);
        ui->btn_videoPlay_Play->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/pause.png);}");
    }
}

void MainPage::pauseClick()
{
    m_readThread->close();
    ui->btn_videoPlay_Play->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/open.png);}");
    ui->btn_videoPlay_Stop->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/stop.png);}");

}

void MainPage::on_playState(ReadThread::PlayState state)
{
    if(state == ReadThread::play)
    {
        ui->btn_videoPlay_Play->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/pause.png);}");
    }
    else
    {
        ui->btn_videoPlay_Play->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/open.png);}");
        ui->btn_videoPlay_Stop->setStyleSheet("QPushButton{border-image: url(:/res/VideoPlay/stop.png);}");
    }
}

void MainPage::recvMsg(const QString &msg)
{
    QString formatMsg = markdownToHtml(msg);
    ui->textEdit_Friend->append(formatMsg);
}

QString MainPage::markdownToHtml(const QString &markdown) {
    QString html = markdown;

    // 替换粗体
    html.replace(QRegularExpression("\\*\\*(.*?)\\*\\*"), "<b>\\1</b>");
    // 替换斜体
    html.replace(QRegularExpression("\\*(.*?)\\*"), "<i>\\1</i>");
    // 替换标题
    html.replace(QRegularExpression("# (.*?)\\n"), "<h1>\\1</h1>");
    // 替换链接
    html.replace(QRegularExpression("\\[([^\\]]+)\\]\\(([^\\)]+)\\)"), "<a href=\"\\2\">\\1</a>");
    // 替换图片
    html.replace(QRegularExpression("!\\[([^\\]]+)\\]\\(([^\\)]+)\\)"), "<img src=\"\\2\" alt=\"\\1\" />");

    // 包裹 HTML 标签
    html = "<html><body>" + html + "<br> </body></html> ";
    return html;
}

void MainPage::updateVisibleWidgets()
{
    // 根据 visibleStartIndex 设置哪些控件可见
    for(int i = 0; i < m_widgetList.size(); ++i)
    {
        m_widgetList[i]->setVisible(i >= m_visibleStartIndex && m_visibleStartIndex + 5);
    }
}

void MainPage::free()
{
    if(m_scrollArea)
    {
        delete m_scrollArea;
    }
    if(m_containerWidget)
    {
        delete m_containerWidget;
    }
    if(m_containerLayout)
    {
        delete m_containerLayout;
    }
    // if(!m_widgetList.isEmpty())
    // {
    //     qDeleteAll(m_widgetList);
    //     m_widgetList.clear();
    // }
    if(m_lastSelectedWidget)
    {
        delete m_lastSelectedWidget;
    }
    if(m_xlsx)
    {
        // delete m_xlsx;
    }
    if(m_readThread)
    {
        m_readThread->close();
        m_readThread->wait();
        // delete m_readThread;
    }
}

void MainPage::setPicture()
{
    QPixmap boyImage(":/res/MainPage/boy.png");
    QPixmap scaledImage = boyImage.scaled(ui->label_avatar->width(), ui->label_avatar->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_avatar->setAlignment(Qt::AlignCenter);
    ui->label_avatar->setPixmap(scaledImage);

    QPixmap wxIcon(":/res/MainPage/wxBackGround.png");
    QPixmap iconScaledImage = wxIcon.scaled(ui->label_wxIcon->width(), ui->label_wxIcon->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_wxIcon->setAlignment(Qt::AlignCenter);
    ui->label_wxIcon->setPixmap(iconScaledImage);
}

MainPage::~MainPage()
{
    free();
    delete ui;
}

void MainPage::exitApp()
{
    QApplication::quit();
}

void MainPage::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0)

    {
        // 滚轮向上
        if (m_visibleStartIndex > 0) {
            --m_visibleStartIndex;
            updateVisibleWidgets();
        }
    }
}
