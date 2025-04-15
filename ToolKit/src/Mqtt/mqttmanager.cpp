#include "mqttmanager.h"
#include <QDebug>

MqttManager::MqttManager(QObject *parent)
    : QObject{parent}
{
    m_mqttClient = std::make_shared<QMqttClient>();
    mqttConnect();
}

void MqttManager::mqttConnect()
{
    mqttConnectSever(mqttHostUrl, mqttPort, mqttClientId, mqttUserName, mqttUserPasswd);
    mqttSubscribe(SubTopicName);
}

void MqttManager::mqttConnectSever(QString hostUrl, QString Port, QString clientId, QString userName, QString userPasswd)
{
    m_mqttClient->setHostname(hostUrl);
    m_mqttClient->setPort(Port.toInt());
    m_mqttClient->setClientId(clientId);
    m_mqttClient->setUsername(userName);
    m_mqttClient->setPassword(userPasswd);
    m_mqttClient->connectToHost();
}

void MqttManager::mqttSubscribe(QString topicName)
{
    qDebug() << "mqttSubscribe **";
    m_mqttClient->subscribe(topicName);
}
