#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

enum class StackPage : int
{
    ChatPage,
    FriendPage,
    CollectPage,
    MomentsPage,
    ToolPage,
    VideoPlayPage,
    OpencvPage
};

class CommonUtils : public QObject
{
    Q_OBJECT
public:
    explicit CommonUtils(QObject *parent = nullptr);

public:
    void sendRequest(const QString& role, const QString& question);

Q_SIGNALS:
    void sendMsg(QString msg);

};

template <typename T>
double add(const T &a, const T &b)
{
    return a + b;
}


#endif // COMMONUTILS_H
