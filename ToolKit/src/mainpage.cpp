#include "mainpage.h"
#include "ui_mainpage.h"

#include <QIcon>
#include <QList>
#include <QScrollBar>
#include <QFileDialog>
#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    QPixmap boyImage(":/res/MainPage/boy.png");
    QPixmap scaledImage = boyImage.scaled(ui->label_avatar->width(), ui->label_avatar->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_avatar->setAlignment(Qt::AlignCenter);
    ui->label_avatar->setPixmap(scaledImage);

    QPixmap wxIcon(":/res/MainPage/wxBackGround.png");
    QPixmap iconScaledImage = wxIcon.scaled(ui->label_wxIcon->width(), ui->label_wxIcon->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_wxIcon->setAlignment(Qt::AlignCenter);
    ui->label_wxIcon->setPixmap(iconScaledImage);

    double a = add(4.5,3.2);
    qDebug() << "a : " << a;

    ui->stackedWidget_side->setCurrentIndex(static_cast<int>(StackPage::ChatPage));

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
        MsgRecord *msgRecord = new MsgRecord();
        m_widgetList.append(msgRecord);
        m_containerLayout->addWidget(msgRecord);
        connect(msgRecord, &MsgRecord::clicked, this, &MainPage::onWidgetClicked);
    }

    updateVisibleWidgets();


    // NEW
    m_xlsx = new XlsxManager();
    m_readThread = new ReadThread();
    connect(m_readThread, &ReadThread::updateImage, ui->widget_VideoPlay, &PlayImage::updateImage, Qt::DirectConnection);
    connect(m_readThread, &ReadThread::playState, this, &MainPage::on_playState);


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
    else if(senderObj == ui->btn_videoPlay_Open)
    {
        openClick();
    }
    else if(senderObj == ui->btn_videoPlay_Pause)
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
    QString strName = QFileDialog::getOpenFileName(this, "Please Choose Your Video !" , "/Users/areay7/Downloads", "视频 (*.mp4 *.m4v *.mov *.avi *.flv);; 其它(*)");
    qDebug() << "strName -----> " << strName;
    if(strName.isEmpty())
    {
        qDebug() << "strName is Empty !";
        return;
    }
    ui->comboBox_url->setCurrentText(strName);
}

void MainPage::openClick()
{
    if(ui->btn_videoPlay_Open->text() == "开始播放")
    {
        m_readThread->open(ui->comboBox_url->currentText());
    }
    else
    {
        m_readThread->close();
    }
}

void MainPage::pauseClick()
{
    if(ui->btn_videoPlay_Pause->text() == "暂停")
    {
        m_readThread->pause(true);
        ui->btn_videoPlay_Pause->setText("继续");
    }
    else
    {
        m_readThread->pause(false);
        ui->btn_videoPlay_Pause->setText("暂停");
    }
}

void MainPage::on_playState(ReadThread::PlayState state)
{
    if(state == ReadThread::play)
    {
        ui->btn_videoPlay_Open->setText("停止播放");
    }
    else
    {
        ui->btn_videoPlay_Open->setText("开始播放");
        ui->btn_videoPlay_Pause->setText("暂停");
    }
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
    if(!m_widgetList.isEmpty())
    {
        qDeleteAll(m_widgetList);
        m_widgetList.clear();
    }
    if(m_lastSelectedWidget)
    {
        delete m_lastSelectedWidget;
    }
    if(m_xlsx)
    {
        delete m_xlsx;
    }
    if(m_readThread)
    {
        m_readThread->close();
        m_readThread->wait();
        delete m_readThread;
    }
}

MainPage::~MainPage()
{
    free();
    delete ui;
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
