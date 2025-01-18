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
public:
    VideoDecode();
    ~VideoDecode();

    bool open(const QString &url = QString());
    QImage read();
    void close();
    bool isEnd();
    const qint64 &pts();

private:
    void initFFmpeg();
    void showError(int err);
    qreal rationalToDouble(AVRational *rational);
    void clear();
    void free();

private:
    AVFormatContext *m_formatContext    = nullptr;
    AVCodecContext  *m_codecContext     = nullptr;
    SwsContext      *m_swsContext       = nullptr;
    AVPacket        *m_packet           = nullptr;
    AVFrame         *m_frame            = nullptr;
    int     m_videoIndex    = 0;
    qint64  m_totalTime     = 0;
    qint64  m_totalFrames   = 0;
    qint64  m_obtainFrames  = 0;
    qint64  m_pts           = 0;
    qreal   m_frameRate     = 0;
    QSize   m_size;
    bool    m_end = false;
    char    *m_error    =   nullptr;
    uchar   *m_buffer   =   nullptr;
};


#endif // VIDEODECODE_H
