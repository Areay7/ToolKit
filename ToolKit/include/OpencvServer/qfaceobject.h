#if 1

#ifndef QFACEOBJECT_H
#define QFACEOBJECT_H

#include <QObject>
#include <seeta/FaceEngine.h>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <memory>



// 人脸数据存储， 人脸检测， 人脸识别
class QFaceObject : public QObject
{
    Q_OBJECT
public:
    explicit QFaceObject(QObject *parent = nullptr);
    ~QFaceObject();

public slots:
    qint64 face_register(cv::Mat& faceimage);
    qint64 face_query(cv::Mat& faceImage);

signals:
    void send_faceid(qint64 faceid);


private:
    std::shared_ptr<seeta::FaceEngine> m_fengineptr;

};

#endif // QFACEOBJECT_H

#endif
