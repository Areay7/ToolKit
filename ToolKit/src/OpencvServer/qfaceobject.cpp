#if 0

#include "qfaceobject.h"

QFaceObject::QFaceObject(QObject *parent)
    : QObject{parent}
{
    // 初始化
    seeta::ModelSetting FDmode("/Users/areay7/Opencv/model/fd_2_00.dat", seeta::ModelSetting::CPU,0);
    seeta::ModelSetting PDmode("/Users/areay7/Opencv/model/pd_2_00_pts5.dat", seeta::ModelSetting::CPU,0);
    seeta::ModelSetting FRmode("/Users/areay7/Opencv/model/fr_2_10.dat", seeta::ModelSetting::CPU,0);

    this->fengineptr = new seeta::FaceEngine(FDmode, PDmode, FRmode);

    // 导入已经有的人脸数据库
    this->fengineptr->Load("./face.db");
}

QFaceObject::~QFaceObject()
{
    delete fengineptr;
}

int64_t QFaceObject::face_register(Mat &faceImage)
{
    // 把 opencv 的 Mat 数据转为 seetaface 数据
    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();

    // 注册返回一个人脸 ID
    int64_t faceId = this->fengineptr->Register(simage);

    if(faceId >= 0)
    {
        fengineptr->Save("./face.db");
    }

    return faceId;
}

int QFaceObject::face_query(Mat &faceImage)
{
    // 把 opencv 的 Mat 数据转为 seetaface 数据
    SeetaImageData simage;
    simage.data = faceImage.data;
    simage.width = faceImage.cols;
    simage.height = faceImage.rows;
    simage.channels = faceImage.channels();
    float similarity = 0;
    // 运算时间较久
    int64_t faceId = fengineptr->Query(simage, &similarity);
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
