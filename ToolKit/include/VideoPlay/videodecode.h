#ifndef VIDEODECODE_H
#define VIDEODECODE_H

#include <QString>
#include <QSize>

struct AVFormatContext;
struct AVCodecContext;
struct AVRational;
struct AVPacket;
struct AVFrame;
struct SwsContext;
struct AVBufferRef;
class QImage;

class VideoDecode
{
    VideoDecode();
    ~VideoDecode();

    bool open(const QString &url = QString());
    QImage read();
    void close();
    bool isEnd();
}


#endif // VIDEODECODE_H
