#if 1

#include "qfaceobject.h"

QFaceObject::QFaceObject(QObject *parent)
    : QObject{parent}
{
    // 初始化
    seeta::ModelSetting FDmode("/Users/areay7/Opencv/model/fd_2_00.dat", seeta::ModelSetting::CPU,0);
    seeta::ModelSetting PDmode("/Users/areay7/Opencv/model/pd_2_00_pts5.dat", seeta::ModelSetting::CPU,0);
    seeta::ModelSetting FRmode("/Users/areay7/Opencv/model/fr_2_10.dat", seeta::ModelSetting::CPU,0);

    m_fengineptr = std::make_shared<seeta::FaceEngine>(FDmode, PDmode, FRmode);
    // this->fengineptr = new seeta::FaceEngine(FDmode, PDmode, FRmode);

    // 导入已经有的人脸数据库
    m_fengineptr->Load("./face.db");
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
        m_fengineptr->Save("./face.db");
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
    qDebug() << "查询相似度 : " << faceId  << " -> "<< similarity;

    if(similarity > 0.7)
    {
        emit send_faceid(faceId);
    }
    else
    {
        emit send_faceid(-1);
    }
    return faceId;
}

#endif
