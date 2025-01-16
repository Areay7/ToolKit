#include "commonbase.h"
#include <iostream>

CommonBase::CommonBase(QObject *parent)
    : QObject{parent}
{

}

QString CommonBase::formatDateTime(const QDateTime &dateTime)
{
    qDebug() << "-------------> formatDateTime";
    return "";
}

void CommonBase::logMessage(const LogType &type, const QString &message)
{
    QString head = "";
    switch (static_cast<int>(type)) {
    case static_cast<int>(LogType::DEBUG):
        head = "<DEBUG>";
        break;
    case static_cast<int>(LogType::ERROR):
        head = "<ERROR>";
        break;
    case static_cast<int>(LogType::FATAL):
        head = "<FATAL>";
        break;
    case static_cast<int>(LogType::INFO):
        head = "<INFO>";
        break;
    case static_cast<int>(LogType::WARN):
        head = "<WARN>";
        break;
    default:
        head = "<INFO>";
        break;
    }
    QString msg = QString("%1  %2").arg(head).arg(message);
    std::cout << msg.toStdString() << std::endl;
}
