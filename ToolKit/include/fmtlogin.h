#ifndef FMTLOGIN_H
#define FMTLOGIN_H

#include <QWidget>
#include "databasemanager.h"
#include <mainpage.h>
#include <commondialog.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class FmtLogin;
}
QT_END_NAMESPACE

class FmtLogin : public QWidget
{
    Q_OBJECT

public:
    FmtLogin(QWidget *parent = nullptr);
    ~FmtLogin();

public:
    void ExitApp();
    bool Register();
    bool Login();

private:
    Ui::FmtLogin *ui;
    MainPage m_MainPage;
    CommonDialog m_box;

    DatabaseManager *t;
};
#endif // FMTLOGIN_H
