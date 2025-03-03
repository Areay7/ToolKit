#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include <memory>
#include <QtMqtt/qmqttclient.h>

// 阿里云 连接参数
#define mqttHostUrl "iot-06z00aqr0zzjelx.mqtt.iothub.aliyuncs.com"
#define mqttPort "1883"
#define mqttClientId "k0etkov8nxp.vechilev_v1|securemode=2,signmethod=hmacsha256,timestamp=1713421876080|"
#define mqttUserName "vechilev_v1&k0etkov8nxp"
#define mqttUserPasswd "10016e531761eb3e36b48e48347c55e821cd7995a34b71d7d83234dc0a411e68"
#define PublishTopicName "/sys/k0etkov8nxp/vechilev_v1/thing/event/property/post"
#define SubTopicName "/sys/k0etkov8nxp/vechilev_v1/thing/event/property/post_reply"

class MqttManager : public QObject
{
    Q_OBJECT
public:
    explicit MqttManager(QObject *parent = nullptr);

    void mqttConnect();

    void mqttConnectSever(QString hostUrl, QString Port, QString clientId, QString userName, QString userPasswd);

    void mqttSubscribe(QString topicName);


    std::shared_ptr<QMqttClient> m_mqttClient;

signals:
};

#endif // MQTTMANAGER_H
