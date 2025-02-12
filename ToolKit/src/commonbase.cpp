#include "commonbase.h"
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
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

QString CommonBase::getCpuUse()
{
    QString res = "";
    QProcess process;

    QString cmd = "/bin/ps -e -o %cpu | /usr/bin/awk '{s+=$1} END {print s}'";
    process.start("/bin/sh", QStringList() << "-c" << cmd);

    if(!process.waitForFinished())
    {
        res = process.errorString();
        qDebug() << "error : " << res;
    }
    else
    {
        res = process.readAll().trimmed();
        qDebug() << res;
    }

    return res;
}

#include "CommonBase.h"
#include <QProcess>
#include <QRegularExpression>
#include <QDebug>

QString CommonBase::getMemoryUse()
{
    QString res = "";
    QProcess process;

    // 执行 top 命令获取内存信息
    QString cmd = "/usr/bin/top -l 1 | grep PhysMem";
    process.start("/bin/sh", QStringList() << "-c" << cmd);

    if (!process.waitForFinished()) {
        res = process.errorString();
        qDebug() << "error: " << res;
        return "Error";
    }

    QString output = process.readAll().trimmed(); // 去除换行符
    qDebug() << "Memory usage:" << output;

    // 提取已使用内存 (G) 和可用内存 (M)
    QRegularExpression regex(R"(PhysMem: (\d+)G used .*?, (\d+)M unused)");
    QRegularExpressionMatch match = regex.match(output);

    if (match.hasMatch()) {
        int usedGB = match.captured(1).toInt();  // 已使用内存 (GB)
        int freeMB = match.captured(2).toInt();  // 空闲内存 (MB)
        qDebug() << "usedGB : " << usedGB;
        qDebug() << "freeMB : " << freeMB;

        // 获取总内存大小（单位 GB）
        int totalGB = usedGB + freeMB / 1024;  // MB 转换为 GB

        if (totalGB > 0) {

            int usagePercent = (usedGB * 100) / totalGB;
            qDebug() << "usedGB : " << usedGB;
            qDebug() << "totalGB : " << totalGB;
            qDebug() << "usagePercent : " << usagePercent;
            res = QString::number(usagePercent) + "%";
            qDebug() << "Extracted memory usage:" << res;
        } else {
            res = "0%";
            qDebug() << "Failed to calculate memory usage";
        }
    } else {
        res = "0%";
        qDebug() << "Failed to extract memory usage";
    }

    return res;
}




