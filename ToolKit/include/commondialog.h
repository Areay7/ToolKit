#ifndef COMMONDIALOG_H
#define COMMONDIALOG_H

#include <QDialog>

namespace Ui {
class CommonDialog;
}

class CommonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommonDialog(QWidget *parent = nullptr);
    ~CommonDialog();

public:
    int setButtonWindow(QString msg, int btnNum,const QString &btnText_1 = "确认", const QString &btnText_2 = "取消", bool is_exec = true);
    void setBarValue(int value);
    void clickOk();
    void clickCancel();

private:
    Ui::CommonDialog *ui;

    // double falseValue;
};

#endif // COMMONDIALOG_H
