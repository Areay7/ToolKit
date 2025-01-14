#include "../include/databasemanager.h"
#include <QDebug>
#include <QSettings>


DatabaseManager* DatabaseManager::instance = nullptr;

bool DatabaseManager::init()
{
    // 读取配置文件
    QSettings settings("E:/work/MyGit/ToolKit/ToolKit/set.ini", QSettings::IniFormat);

    // 获取配置 若不存在则使用默认
    QString driver = settings.value("Database/Driver", "QMYSQL").toString();
    QString host = settings.value("Database/Host", "127.0.0.1").toString();
    QString user = settings.value("Database/User", "root").toString();
    QString password = settings.value("Database/Password", "123456").toString();

    qDebug() << "driver : " << driver;
    qDebug() << "host : " << host;
    qDebug() << "user : " << user;
    qDebug() << "password : " << password;
    m_db = QSqlDatabase::addDatabase(driver);
    bool flag = m_db.isValid();

    if (flag)
    {
        qDebug() << "success";

    }
    else
    {
        qDebug() << "fail";
    }
    return flag;
}
