#include "msgrecord.h"
#include "ui_msgrecord.h"
#include <QVBoxLayout>
#include <QLabel>

MsgRecord::MsgRecord(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MsgRecord)
{
    ui->setupUi(this);

    setFixedSize(230,90);
    setWindowFlag(Qt::FramelessWindowHint);



    // 头像
    QLabel *avatarLabel = new QLabel(this);
    avatarLabel->setFixedSize(45, 45);
    // 固定头像大小
    avatarLabel->setPixmap(QPixmap(":/res/MainPage/gril.png").scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // 中间部分（名称 + 消息）
    QLabel *nameLabel = new QLabel("User Name", this);
    nameLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    QLabel *messageLabel = new QLabel("Last message is", this);
    messageLabel->setStyleSheet("color: gray; font-size: 12px;");
    QVBoxLayout *middleLayout = new QVBoxLayout; middleLayout->addWidget(nameLabel);
    middleLayout->addWidget(messageLabel); middleLayout->setSpacing(5);
    // 右侧部分（时间）
    QLabel *timeLabel = new QLabel("11:30", this);
    timeLabel->setStyleSheet("color: gray; font-size: 12px;");
    timeLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
    // 主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(avatarLabel, 1);
    // 左侧头像，占 1/3 宽度
    mainLayout->addLayout(middleLayout, 2);
    // 中间部分，占 1/3 宽度
    mainLayout->addWidget(timeLabel, 1);
    // 右侧时间，占 1/3 宽度
    mainLayout->setContentsMargins(10, 10, 10, 10);
    // 设置间距
    mainLayout->setSpacing(15);
    setLayout(mainLayout);

}

MsgRecord::~MsgRecord()
{
    delete ui;
}
