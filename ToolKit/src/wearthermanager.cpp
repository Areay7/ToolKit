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
    QJsonObject objData = rootObj.value("data").toObject();

    float m_wendu = objData.value("wendu").toString().toFloat();
    float m_shidu = objData.value("shidu").toString().toFloat();

    emit sendInfo(m_wendu, m_shidu);
    qDebug() << "------------> wendu : " << m_wendu;
    qDebug() << "------------> shidu : " << m_shidu;
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

void WeartherManager::getCityName() {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://2024.ipchaxun.com/"));
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &WeartherManager::onCityNameFinished);
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

void WeartherManager::onCityNameFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        QString ret = jsonObj["ret"].toString();
        if (ret == "ok") {
            QJsonArray data = jsonObj["data"].toArray();
            QString country = data[0].toString();
            QString province = data[1].toString();
            QString city = data[2].toString();

            qDebug() << "*********city : " << city;
            emit cityFetched(country, province, city);
        } else {
            emit errorOccurred("Failed to fetch city data.");
        }
    } else {
        emit errorOccurred(reply->errorString());
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
