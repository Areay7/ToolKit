#ifndef COMMONDIALOG_H
#define COMMONDIALOG_H

#include <QDialog>
#include <QUrl>
#include <QTimer>
#include <QSoundEffect>


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

class Cartoon : public QObject
{
    Q_OBJECT
public:
    explicit Cartoon(QObject *parent = nullptr);
    ~Cartoon();

    static void playWeChatSound();
};


#endif // COMMONDIALOG_H
