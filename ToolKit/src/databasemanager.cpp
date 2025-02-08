#include "databasemanager.h"
#include <QDebug>
#include <QSettings>
#include <QSqlError>

DatabaseManager* DatabaseManager::instance = nullptr;

bool DatabaseManager::Init()
{
    // 获取当前 .pro 文件所在的目录
    QString proFilePath = QString(PRO_FILE_PWD);

    // 拼接路径
    QString filePath = proFilePath + "/set.ini";

    // 读取配置文件
    QSettings settings(filePath, QSettings::IniFormat);

    // 获取配置 若不存在则使用默认
    QString driver = settings.value("Database/Driver", "QMYSQL").toString();
    QString host = settings.value("Database/Host", "127.0.0.1").toString();
    QString user = settings.value("Database/User", "root").toString();
    QString password = settings.value("Database/Password", "123456").toString();

    qDebug() << "driver : " << driver;
    qDebug() << "host : " << host;
    qDebug() << "user : " << user;
    // qDebug() << "password : " << password;
    m_db = QSqlDatabase::addDatabase(driver);
    bool flag = m_db.isValid();

    if (flag)
    {
        qDebug() << "driver success";
        if(driver == "QMYSQL")
        {
            m_db.setDatabaseName("toolkit");
            m_db.setHostName(host);
            m_db.setPort(3306);
            m_db.setUserName(user);
            m_db.setPassword(password);
            flag = m_db.open();
        }

    }
    else
    {
        qDebug() << "fail";
    }
    return flag;
}

bool DatabaseManager::InsertUser(const QString &userName, const QString &userAccount, const QString &userPassword)
{
    bool res = false;
    if(!m_db.isOpen()) return res;

    QSqlQuery query;
    query.prepare("INSERT INTO user (name, account, password) VALUES (?, ?, ?)");
    query.addBindValue(userName);
    query.addBindValue(userAccount);
    query.addBindValue(userPassword);

    if(!query.exec())
    {
        qDebug() << "Insert fail !";
        res = false;
    }
    else
    {
        qDebug() << "Insert success !";
        res = true;
    }

    return res;
}

bool DatabaseManager::Login(const QString &userName, const QString &userAccount, const QString &userPassword)
{
    bool res = false;
    if(!m_db.isOpen()) return res;

    QSqlQuery query;
    query.prepare("SELECT password FROM user WHERE account =?");
    query.addBindValue(userAccount);

    if(!query.exec())
    {
        qDebug() << "Check fail !";
        res = false;
        return res;
    }

    if (query.next())
    {
        QString resPasswd = query.value(0).toString();
        qDebug() << "resPasswd : " << resPasswd;
        if(resPasswd == userPassword)
        {
            qDebug() << "Check success !";
            res = true;
        }
    }
    else
    {
        qDebug() << "Account not found!";
    }

    qDebug() << "return ------->  " << res;
    return res;
}


