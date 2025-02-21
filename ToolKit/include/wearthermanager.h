#ifndef WEARTHERMANAGER_H
#define WEARTHERMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <memory>

class WeartherManager : QObject
{
    Q_OBJECT
public:
    WeartherManager();

private:
    std::shared_ptr<WeartherManager> m_NetAccessManager;

};

#endif // WEARTHERMANAGER_H
