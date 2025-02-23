#ifndef WEARTHERMANAGER_H
#define WEARTHERMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <memory>

#include <QMap>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

class WeartherManager : public QObject
{
    Q_OBJECT
public:
    WeartherManager();
    void parseJson(QByteArray &byteArray);
    void getWeatherInfo(QString cityName);

private:
    QNetworkAccessManager *m_NetAccessManager;


private slots:
    void onReplied(QNetworkReply* reply);

};


class WeatherTool
{
private:
    static QMap<QString, QString> m_cityMap;

public:
    static void initCityMap();
    static QString getCityCode(QString cityName);

};



#endif // WEARTHERMANAGER_H
