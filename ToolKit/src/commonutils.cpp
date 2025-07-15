#include "commonutils.h"

#define DeepSeek 0
#define KiMi 1

#if DeepSeek
const QString API_URL = "https://api.deepseek.com/chat/completions";
const QString API_KEY = "sk-6050ef86e2d542208302ccb5e1aba110";

#elif KiMi
const QString API_URL = "https://api.moonshot.cn/v1";
// const QString API_KEY = "sk-tyU3wVYqHCFoWNnUtXM0PMdFGG4VtBXEtu7HNn4UH15LFVHW";
const QString API_KEY = "sk-Tg4tDuLuUxE4MioIOjLYCI3ENutskpOAiiyZSYBNJ5AhinEe";
#endif

CommonUtils::CommonUtils(QObject *parent)
    : QObject{parent}
{

}


/*
* @ parm role [in] "指定希望Ai是一个什么样的角色来协助你完成工作"
* @ parm question [in] "你需要提问的问题"
* @ remarks 通过void MainPage::recvMsg(const QString &msg)槽函数去接收AI的回复
*/

void CommonUtils::sendRequest(const QString& role, const QString& question) {
    qDebug() << "***********API*************";

#if DeepSeek
    // 创建网络管理器
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    // 构造请求
    QNetworkRequest request((QUrl(API_URL)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer " + API_KEY).toUtf8());

    // 构造 JSON 数据
    QJsonObject systemMessage {{"role", "system"}, {"content", role}};
    QJsonObject userMessage {{"role", "user"}, {"content", question}};
    QJsonArray messages = {systemMessage, userMessage};

    QJsonObject requestData;
    requestData["model"] = "deepseek-chat";
    // requestData["model"] = "deepseek-reasoner";   // R1模型
    requestData["messages"] = messages;
    requestData["stream"] = false;

    // 发送 POST 请求
    QNetworkReply* reply = manager->post(request, QJsonDocument(requestData).toJson());

    // 处理返回的数据
    QObject::connect(reply, &QNetworkReply::finished, [this,reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            // qDebug() << "API Response:" << responseData;

            // 解析 JSON 数据
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
            if (jsonResponse.isObject()) {
                QJsonObject jsonObject = jsonResponse.object();
                if (jsonObject.contains("choices")) {
                    QJsonArray choices = jsonObject["choices"].toArray();
                    if (!choices.isEmpty()) {
                        QString aiResponse = choices[0].toObject()["message"].toObject()["content"].toString();
                        qDebug() << "ai : " << aiResponse;
                        emit sendMsg(aiResponse);
                    }
                }
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
#elif KiMi
    // 创建网络管理器
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    // 构造请求
    QNetworkRequest request((QUrl("https://api.moonshot.cn/v1/chat/completions")));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer " + API_KEY).toUtf8());

    // 构造 JSON 数据
    QJsonObject systemMessage {{"role", "system"}, {"content", role}};
    QJsonObject userMessage {{"role", "user"}, {"content", question}};
    QJsonArray messages = {systemMessage, userMessage};

    QJsonObject requestData;
    requestData["model"] = "moonshot-v1-8k";
    requestData["messages"] = messages;
    requestData["stream"] = false;

    // 发送 POST 请求
    QNetworkReply* reply = manager->post(request, QJsonDocument(requestData).toJson());

    // 处理返回的数据
    QObject::connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            // qDebug() << "API Response:" << responseData;

            // 解析 JSON 数据
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
            if (jsonResponse.isObject()) {
                QJsonObject jsonObject = jsonResponse.object();
                if (jsonObject.contains("choices")) {
                    QJsonArray choices = jsonObject["choices"].toArray();
                    if (!choices.isEmpty()) {
                        QString aiResponse = choices[0].toObject()["message"].toObject()["content"].toString();
                        qDebug() << "AI Response:" << aiResponse;
                        emit sendMsg(aiResponse);
                    }
                }
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
#else
    qDebug() << "KiMi API not selected!";
#endif

}


