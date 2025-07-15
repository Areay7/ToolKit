#if 0

#include "selectwin.h"

SelectWin::SelectWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SelectWin)
{
    ui->setupUi(this);
    model = new QSqlTableModel();
}

SelectWin::~SelectWin()
{
    delete ui;
}

void SelectWin::on_selectButton_clicked()
{
    if(ui->empRb->isChecked())
    {
        // 设置员工表格
        model->setTable("employee");
    }
    if(ui->attRb->isChecked())
    {
        model->setTable("attendance");
    }

    // 设置过滤器
    // model->setFilter("name=");

    // 查询
    model->select();

    ui->tableView->setModel(model);
}

#endif
