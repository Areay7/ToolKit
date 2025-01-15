#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>
#include <QDebug>

enum class DataBaseDriver : char
{
    MySQL,
    SQLite,
    PostgreSQL,
    Oracle
};

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager* getInstance()
    {
        static QMutex mutex;
        if (nullptr == instance)
        {
            QMutexLocker locker(&mutex);
            if(nullptr == instance)
            {
                instance = new DatabaseManager();
                if(instance->Init())
                {
                    qDebug() << "init success ! ";
                }
                else
                {
                    DatabaseManager::destroyInstance();
                }
            }
        }
        return instance;
    }

    static void destroyInstance()
    {
        if (nullptr == instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    bool Init();
    bool InsertUser(const QString &userName, const QString &userAccount, const QString &userPassword);
    bool Login(const QString &userName, const QString &userAccount, const QString &userPassword);

private:
    DatabaseManager() {}
    DatabaseManager(const DatabaseManager &) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    ~DatabaseManager() {}

    static DatabaseManager* instance;
    QSqlDatabase m_db;
};




#endif // DATABASEMANAGER_H
