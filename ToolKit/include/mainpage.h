#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <msgrecord.h>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

private:
    Ui::MainPage *ui;
    MsgRecord msg;
};

#endif // MAINPAGE_H
