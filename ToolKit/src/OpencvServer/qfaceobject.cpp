#if 1

#include "qfaceobject.h"
#include <QDebug>

const QString proFilePath = QString(PRO_FILE_PWD);

QFaceObject::QFaceObject(QObject *parent)
    : QObject{parent}
{
    // 初始化
    const std::string FDmode_PATH = QString(proFilePath + "/3rd_party/Opencv/model/fd_2_00.dat").toStdString().c_str();
    const std::string PDmode_PATH = QString(proFilePath + "/3rd_party/Opencv/model/pd_2_00_pts5.dat").toStdString().c_str();
    const std::string FRmode_PATH = QString(proFilePath + "/3rd_party/Opencv/model/fr_2_10.dat").toStdString().c_str();

    seeta::ModelSetting FDmode(FDmode_PATH, seeta::ModelSetting::CPU,0);
    seeta::ModelSetting PDmode(PDmode_PATH, seeta::ModelSetting::CPU,0);
    seeta::ModelSetting FRmode(FRmode_PATH, seeta::ModelSetting::CPU,0);

    m_fengineptr = std::make_shared<seeta::FaceEngine>(FDmode, PDmode, FRmode);

    // 导入已经有的人脸数据库
    bool flag = m_fengineptr->Load(QString(proFilePath + "/data/face.db").toStdString().c_str());
    qDebug() << QString(proFilePath + "/data/face.db").toStdString().c_str();
    qDebug() << "-------------------------- Load : " << flag << "-------------------------------";
}

QFaceObject::~QFaceObject()
{
    // delete fengineptr;
}

qint64 QFaceObject::face_register(cv::Mat &faceImage)
{
    // 把 opencv 的 Mat 数据转为 seetaface 数据
    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();

    // 注册返回一个人脸 ID
    qint64 faceId = m_fengineptr->Register(simage);

    if(faceId >= 0)
    {
        m_fengineptr->Save(QString(proFilePath + "/data/face.db").toStdString().c_str());
    }

    return faceId;
}

qint64 QFaceObject::face_query(cv::Mat &faceImage)
{
    // 把 opencv 的 Mat 数据转为 seetaface 数据
    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();
    float similarity = 0;
    // 运算时间较久
    qint64 faceId = m_fengineptr->Query(simage, &similarity);

    qDebug() << "查询相似度 : " << faceId  << " ======= "<< similarity;

    if(similarity > 0.7)
    {
        emit sendFaceId(faceId);
    }
    else
    {
        emit sendFaceId(-1);
    }
    return faceId;
}

#endif
