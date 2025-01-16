#include "mainpage.h"
#include "ui_mainpage.h"
#include <QIcon>


MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    QPixmap chatImage(":/res/MainPage/chat_press.png");

    QPixmap boyImage(":/res/MainPage/boy.png");
    QPixmap scaledImage = boyImage.scaled(ui->label_avatar->width(), ui->label_avatar->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_avatar->setAlignment(Qt::AlignCenter);
    ui->label_avatar->setPixmap(scaledImage);

    // // QTableWidget *table = new QTableWidget(this);
    // ui->tableWidget->setColumnCount(3); // 设置列数：头像、时间、内容
    // ui->tableWidget->setHorizontalHeaderLabels({"头像", "时间", "内容"});
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 列自适应宽度
    // ui->tableWidget->verticalHeader()->setVisible(false); // 隐藏行头
    // ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    // ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection); // 禁止选择



    msg.show();

}

MainPage::~MainPage()
{
    delete ui;
}
