#include "commonutils.h"

const QString API_URL = "https://api.deepseek.com/chat/completions";
const QString API_KEY = "sk-6050ef86e2d542208302ccb5e1aba110";  // 替换为你的 API Key

CommonUtils::CommonUtils(QObject *parent)
    : QObject{parent}
{

}

void CommonUtils::sendRequest() {
    // 创建网络管理器
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    // 构造请求
    QNetworkRequest request((QUrl(API_URL)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer " + API_KEY).toUtf8());

    // 构造 JSON 数据
    QJsonObject systemMessage {{"role", "system"}, {"content", "你是一名资深的C++程序员"}};
    QJsonObject userMessage {{"role", "user"}, {"content", "如何高效学习Linux C++ QT，并且快速适应工作要求"}};
    QJsonArray messages = {systemMessage, userMessage};

    QJsonObject requestData;
    // requestData["model"] = "deepseek-chat";
    requestData["model"] = "deepseek-reasoner";
    requestData["messages"] = messages;
    requestData["stream"] = false;

    // 发送 POST 请求
    QNetworkReply* reply = manager->post(request, QJsonDocument(requestData).toJson());

    // 处理返回的数据
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "API Response:" << responseData;

            // 解析 JSON 数据
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
            if (jsonResponse.isObject()) {
                QJsonObject jsonObject = jsonResponse.object();
                if (jsonObject.contains("choices")) {
                    QJsonArray choices = jsonObject["choices"].toArray();
                    if (!choices.isEmpty()) {
                        QString aiResponse = choices[0].toObject()["message"].toObject()["content"].toString();
                        qDebug() << "AI Response:" << aiResponse;
                    }
                }
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}


