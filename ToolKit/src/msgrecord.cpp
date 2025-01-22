#include "msgrecord.h"
#include "ui_msgrecord.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>


MsgRecord::MsgRecord(const QString &userName,  const QString &lastMsg,
                     const QString &time,  const QString &avatarPath, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MsgRecord)
{
    ui->setupUi(this);

    // setFixedSize(230, 90);
    setWindowFlag(Qt::FramelessWindowHint);

    // 创建一个背景容器
    QWidget *backgroundWidget = new QWidget(this);
    backgroundWidget->setGeometry(0, 0, width(), height());  // 设置背景容器的大小与 MsgRecord 一致
    backgroundWidget->setStyleSheet("background-color: transparent;"); // 设置背景颜色为灰色

    // 头像部分
    QLabel *avatarLabel = new QLabel(backgroundWidget); // 将头像添加到 backgroundWidget 上
    avatarLabel->setFixedSize(50, 50);
    avatarLabel->setPixmap(QPixmap(avatarPath).scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // 中间部分（名称 + 消息）
    QLabel *nameLabel = new QLabel(userName, backgroundWidget);
    nameLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

    QLabel *messageLabel = new QLabel(lastMsg, backgroundWidget);
    messageLabel->setStyleSheet("color: gray; font-size: 12px;");

    QVBoxLayout *middleLayout = new QVBoxLayout;
    middleLayout->addWidget(nameLabel);
    middleLayout->addWidget(messageLabel);
    middleLayout->setSpacing(5);

    // 右侧部分（时间）
    QLabel *timeLabel = new QLabel(time, backgroundWidget);
    timeLabel->setStyleSheet("color: gray; font-size: 12px;");
    timeLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);

    // 主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(backgroundWidget);
    mainLayout->addWidget(avatarLabel, 1);   // 左侧头像，占 1/3 宽度
    mainLayout->addLayout(middleLayout, 2);   // 中间部分，占 2/3 宽度
    mainLayout->addWidget(timeLabel, 1);      // 右侧时间，占 1/3 宽度
    mainLayout->setSpacing(0);

    // 设置布局的间距和边距
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(15);

    // 设置 backgroundWidget 为 MsgRecord 的主布局
    setLayout(new QVBoxLayout());
    layout()->addWidget(backgroundWidget);
    qDebug() << "7777777***********";
}



MsgRecord::~MsgRecord()
{
    delete ui;
}

void MsgRecord::setSelected(bool selected)
{
    this->m_selected = selected;

    // 获取背景容器
    QWidget *backgroundWidget = findChild<QWidget *>();

    if (backgroundWidget) {
        // 如果选中，背景变为灰色
        if (selected) {
            backgroundWidget->setStyleSheet("background-color: gray;");
        } else {
            backgroundWidget->setStyleSheet("background-color: transparent;");
        }
    }
}

bool MsgRecord::isSelected() const
{
    return m_selected;
}

void MsgRecord::mousePressEvent(QMouseEvent *event)
{
    emit clicked(this);
}
