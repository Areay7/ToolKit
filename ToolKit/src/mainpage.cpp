#include "mainpage.h"
#include "ui_mainpage.h"
#include "commonutils.h"
#include "commonbase.h"
#include <QIcon>
#include <QList>
#include <QDebug>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    // QPixmap chatImage(":/res/MainPage/chat_press.png");

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
        connect(btn, &QPushButton::clicked, this, &MainPage::SwitchStatckPage);
    }


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
}

void MainPage::SwitchStatckPage()
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

}

void MainPage::onWidgetClicked(MsgRecord *msgRecord)
{
    if(m_lastSelectedWidget)
    {
        m_lastSelectedWidget->m_setSelected(false); // 恢复上一个选中的控件样式
    }

    msgRecord->m_setSelected(true);
    m_lastSelectedWidget = msgRecord;
}

void MainPage::updateVisibleWidgets()
{
    // 根据 visibleStartIndex 设置哪些控件可见
    for(int i = 0; i < m_widgetList.size(); ++i)
    {
        m_widgetList[i]->setVisible(i >= m_visibleStartIndex && m_visibleStartIndex + 5);
    }
}

MainPage::~MainPage()
{
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
