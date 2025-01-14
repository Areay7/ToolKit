#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>
#include <iostream>

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
                if(!instance->init())
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

    bool init();

private:
    DatabaseManager() {}
    DatabaseManager(const DatabaseManager &) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    ~DatabaseManager() {}

    static DatabaseManager* instance;
    QSqlDatabase m_db;
};




#endif // DATABASEMANAGER_H
