#ifndef COMMONBASE_H
#define COMMONBASE_H

#include <QObject>
#include <QDebug>

enum class LogType : int
{
    INFO = 1,    // 信息日志
    DEBUG = 2,   // 调试日志
    WARN = 3,    // 警告日志
    ERROR = 4,   // 错误日志
    FATAL = 5    // 致命错误日志
};

class CommonBase : public QObject
{
    Q_OBJECT
public:
    explicit CommonBase(QObject *parent = nullptr);

public:
    static QString formatDateTime(const QDateTime &dateTime);
    static void logMessage(const LogType &type, const QString &message);
    static QString getCpuUse();
    static QString getMemoryUse();


signals:

};

#endif // COMMONBASE_H
