#include "databasemanager.h"
#include <QDebug>


DatabaseManager* DatabaseManager::instance = nullptr;

bool DatabaseManager::init()
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
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
