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

    addWeatherPicTure();

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

    float cur_temp = objData.value("wendu").toVariant().toFloat();
    float cur_humi = objData.value("shidu").toVariant().toFloat();

    QJsonArray forecastArr = objData.value("forecast").toArray();
    QJsonObject objforecast = forecastArr[0].toObject();


    QString cur_type = objforecast.value("type").toString();

    QString s;
    s = objforecast.value("high").toString().split(" ").at(1);
    s = s.left(s.length() - 1);
    QString today_high = s;
    s = objforecast.value("low").toString().split(" ").at(1);
    s = s.left(s.length() - 1);
    QString today_low = s;

    emit sendInfo(cur_temp, cur_humi, cur_type, today_high, today_low);
    qDebug() << "------------> wendu : " << cur_temp;
    qDebug() << "------------> shidu : " << cur_humi;
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
    qDebug() << "<<<<<<<<<<<<" << __FUNCTION__ << ">>>>>>>>>>>>  5 ";
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://2024.ipchaxun.com/"));
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &WeartherManager::onCityNameFinished);
    qDebug() << "<<<<<<<<<<<<" << __FUNCTION__ << ">>>>>>>>>>>>  6 ";
    emit cityFetched("中国", "广东", "深圳");
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

void WeartherManager::addWeatherPicTure()
{
    //天气对应图标
    m_typeMap.insert("暴雪",":/res/Weather/type/BaoXue.png");
    m_typeMap.insert("暴雨",":/res/Weather/type/BaoYu.png");
    m_typeMap.insert("暴雨到暴雪",":/res/Weather/type/BaoYuDaoDaBaoYu.png");
    m_typeMap.insert("大暴雨",":/res/Weather/type/DaBaoYu.png");
    m_typeMap.insert("大暴雨到大暴雪",":/res/Weather/type/DaBaoYuDaoTeDaBaoYu.png");
    m_typeMap.insert("大到暴雪",":/res/Weather/type/DaDaoBaoXue.png");
    m_typeMap.insert("大到暴雨",":/res/Weather/type/DaDaoBaoYu.png");
    m_typeMap.insert("大雪",":/res/Weather/type/DaXue.png");
    m_typeMap.insert("大雨",":/res/Weather/type/DaYu.png");
    m_typeMap.insert("冻雨",":/res/Weather/type/DongYu.png");
    m_typeMap.insert("多云",":/res/Weather/type/DuoYun.png");
    m_typeMap.insert("浮尘",":/res/Weather/type/FuChen.png");
    m_typeMap.insert("雷阵雨",":/res/Weather/type/LeiZhenYu.png");
    m_typeMap.insert("雷阵雨伴有冰雹",":/res/Weather/type/LeiZhenYuBanYouBingBao.png");
    m_typeMap.insert("霾",":/res/Weather/type/Mai.png");
    m_typeMap.insert("强沙尘暴",":/res/Weather/type/QiangShaChenBao.png");
    m_typeMap.insert("晴",":/res/Weather/type/Qing.png");
    m_typeMap.insert("沙尘暴",":/res/Weather/type/ShaChenBao.png");
    m_typeMap.insert("特大暴雨",":/res/Weather/type/TeDaBaoYu.png");
    m_typeMap.insert("雾",":/res/Weather/type/Wu.png");
    m_typeMap.insert("小到中雨",":/res/Weather/type/XiaoDaoZhongYu.png");
    m_typeMap.insert("小到中雪",":/res/Weather/type/XiaoDaoZhongXue.png");
    m_typeMap.insert("小雪",":/res/Weather/type/XiaoXue.png");
    m_typeMap.insert("小雨",":/res/Weather/type/XiaoYu.png");
    m_typeMap.insert("雪",":/res/Weather/type/Xue.png");
    m_typeMap.insert("扬沙",":/res/Weather/type/YangSha.png");
    m_typeMap.insert("阴",":/res/Weather/type/Yin.png");
    m_typeMap.insert("雨",":/res/Weather/type/Yu.png");
    m_typeMap.insert("雨夹雪",":/res/Weather/type/YuJiaXue.png");
    m_typeMap.insert("阵雨",":/res/Weather/type/ZhenYu.png");
    m_typeMap.insert("阵雪",":/res/Weather/type/ZhenXue.png");
    m_typeMap.insert("中雨",":/res/Weather/type/ZhongYu.png");
    m_typeMap.insert("中雪",":/res/Weather/type/ZhongXue.png");
}

void WeartherManager::onCityNameFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

#if 0
        QString ret = jsonObj["ret"].toString();
        if (ret == "ok") {
            QJsonArray data = jsonObj["data"].toArray();
            QString country = data[0].toString();
            QString province = data[1].toString();
            QString city = data[2].toString();

            qDebug() << "*********city : " << city;
            emit cityFetched(country, province, city);
        } else {
#endif
            emit cityFetched("中国", "广东", "深圳");
            emit errorOccurred("Failed to fetch city data.");
        }
#if 0
    } else {
        emit errorOccurred(reply->errorString());
    }
#endif
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
