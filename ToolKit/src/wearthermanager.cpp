#include "wearthermanager.h"
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

QMap<QString, QString> WeatherTool::m_cityMap;

WeartherManager::WeartherManager()
{
    m_NetAccessManager = new QNetworkAccessManager();

    connect(m_NetAccessManager, &QNetworkAccessManager::finished, this, &WeartherManager::onReplied);
}

void WeartherManager::parseJson(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(byteArray, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug() << "parseJson Error";
        return;
    }
    QJsonObject rootObj = doc.object();
    qDebug() << rootObj.value("message").toString();
}

void WeartherManager::getWeatherInfo(QString cityName)
{
    qDebug() << "<<<<<<<<<<<<" << __FUNCTION__ << ">>>>>>>>>>>>  1 ";
    QString cityCode = WeatherTool::getCityCode(cityName);
    qDebug() << "<<<<<<<<<<<<" << __FUNCTION__ << ">>>>>>>>>>>>  2 ";
    if(cityCode.isEmpty())
    {
        qDebug() << "请检查输入的城市是否正确！";
        return;
    }
    qDebug() << "<<<<<<<<<<<<" << __FUNCTION__ << ">>>>>>>>>>>>  3 ";
    QUrl url("http://t.weather.itboy.net/api/weather/city/" + cityCode);
    qDebug() << "cityCode ----> " << cityCode;
    m_NetAccessManager->get(QNetworkRequest(url));
    qDebug() << "<<<<<<<<<<<<" << __FUNCTION__ << ">>>>>>>>>>>>  4 ";
}

void WeartherManager::onReplied(QNetworkReply* reply)
{
    qDebug() << "reply !";

    qint32 status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "url : " << reply->url();
    qDebug() << "status code : " << status_code;

    if(reply->error() != QNetworkReply::NoError || status_code != 200)
    {
        qWarning() << "天气数据请求失败！";
    }
    else
    {
        QByteArray byteArray = reply->readAll();
        qDebug() << "Read All : " << byteArray.data();
        parseJson(byteArray);
    }
    reply->deleteLater();
}

void WeatherTool::initCityMap()
{
    QString proFIlePath = QString(PRO_FILE_PWD);

    QString filePath = proFIlePath + "/setting/citycode-2019-08-23.json";

    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray json = file.readAll();
    file.close();


    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(json, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug() << "Parse Json Error !";
        return;
    }

    QJsonArray cities = doc.array();
    for(int i = 0; i < cities.size(); ++i)
    {
        QString city_name = cities[i].toObject().value("city_name").toString();
        QString city_code = cities[i].toObject().value("city_code").toString();

        if(city_code.size() > 0)
        {
            m_cityMap.insert(city_name, city_code);
        }
    }
}

QString WeatherTool::getCityCode(QString cityName)
{
    if(m_cityMap.isEmpty())
    {
        initCityMap();
    }

    QMap<QString, QString>::iterator it = m_cityMap.find(cityName);
    if(it == m_cityMap.end())
    {
        it = m_cityMap.find(cityName + "市");

    }
    if(it != m_cityMap.end())
    {
        return it.value();
    }

    return "";
}
