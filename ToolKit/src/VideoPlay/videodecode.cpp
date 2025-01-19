#include "videodecode.h"
#include <QDebug>
#include <QImage>
#include <QMutex>
#include <qdatetime.h>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}

#define ERROR_LEN 1024
#define PRINT_LOG 1

static const int DECODEC_THREAD_COUNT = 8;

VideoDecode::VideoDecode()
{
    // initFFmpeg();

    m_error = new char[ERROR_LEN];
}

VideoDecode::~VideoDecode()
{
    close();
}

void VideoDecode::initFFmpeg()
{
    static bool isFirst = true;
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if(isFirst)
    {
        // av_register_all();
        avformat_network_init();
        isFirst = false;
    }
}

void VideoDecode::showError(int err)
{

}

qreal VideoDecode::rationalToDouble(AVRational *rational)
{

}

void VideoDecode::clear()
{

}

void VideoDecode::free()
{

}

bool VideoDecode::open(const QString &url)
{
    if(url.isNull()) return false;

    AVDictionary *dict = nullptr;
    av_dict_set(&dict, "rtsp_transport", "tcp", 0);
    av_dict_set(&dict, "max_delay", "3", 0);
    av_dict_set(&dict, "timeout", "1000000", 0);

    int ret = avformat_open_input(&m_formatContext,
                                  url.toStdString().data(),
                                  nullptr,
                                  &dict);

    if(dict)
    {
        av_dict_free(&dict);
    }

    if(ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    ret = avformat_find_stream_info(m_formatContext, nullptr);
    if(ret < 0)
    {
        showError(ret);
        free();
        return false;
    }
    m_totalTime = m_formatContext->duration / (AV_TIME_BASE / 1000);  // ms
#if PRINT_LOG
    qDebug() << QString("视频总时长 : %1 ms, [%2] ").arg(m_totalTime).arg(QTime::fromMSecsSinceStartOfDay(int(m_totalTime)).toString("HH:mm:ss zzz"));
#endif

    m_videoIndex = av_find_best_stream(m_formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if(m_videoIndex < 0)
    {
        showError(m_videoIndex);
        free();
        return false;
    }

    AVStream *videoStream = m_formatContext->streams[m_videoIndex];

    m_size.setWidth(videoStream->codecpar->width);
    m_size.setHeight(videoStream->codecpar->height);
    m_frameRate = rationalToDouble(&videoStream->avg_frame_rate);

    const AVCodec *codec = avcodec_find_decoder(videoStream->codecpar->codec_id);
    m_totalFrames = videoStream->nb_frames;

#if PRINT_LOG
    qDebug() << QString("分辨率 : [w:%1 h:%2] 帧率: %3 总帧数: %4 解码器: %5")
                    .arg(m_size.width()).arg(m_size.height()).arg(m_frameRate).arg(m_totalFrames).arg(codec->name);
#endif

    m_codecContext = avcodec_alloc_context3(codec);
    if(!m_codecContext)
    {
#if PRINT_LOG
        qWarning() << "创建视频解码器上下文失败！";
#endif
        free();
        return false;
    }

    ret = avcodec_parameters_to_context(m_codecContext, videoStream->codecpar);
    if(ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    m_codecContext->flags2 |= AV_CODEC_FLAG2_FAST;
    m_codecContext->thread_count = DECODEC_THREAD_COUNT;

    ret = avcodec_open2(m_codecContext, nullptr, nullptr);
    if(ret < 0)
    {
        showError(ret);
        free();
        return false;
    }

    m_packet = av_packet_alloc();
    if(!m_packet)
    {
#if PRINT_LOG
        qWarning() << "av_packet_alloc() Error！";
#endif
        free();
        return false;
    }

    m_frame = av_frame_alloc();
    if(!m_frame)
    {
#if PRINT_LOG
        qWarning() << "av_frame_alloc() Error！";
#endif
        free();
        return false;
    }

    int size = av_image_get_buffer_size(AV_PIX_FMT_BGRA, m_size.width(), m_size.height(), 4);
    m_buffer = new uchar[size + 1000];
    m_end = false;

    return true;
}

QImage VideoDecode::read()
{
    if(!m_formatContext)
    {
        return QImage();
    }

    int readRet = av_read_frame(m_formatContext, m_packet);
    if(readRet < 0)
    {
        avcodec_send_packet(m_codecContext, m_packet);
    }
    else
    {
        if(m_packet->stream_index == m_videoIndex)
        {
            // 计算当前帧时间（毫秒）
#if 1       // 方法一：适用于所有场景，但是存在一定误差
            m_packet->pts = qRound64(m_packet->pts * (1000 * rationalToDouble(&m_formatContext->streams[m_videoIndex]->time_base)));
            m_packet->dts = qRound64(m_packet->dts * (1000 * rationalToDouble(&m_formatContext->streams[m_videoIndex]->time_base)));
#else       // 方法二：适用于播放本地视频文件，计算每一帧时间较准，但是由于网络视频流无法获取总帧数，所以无法适用
            m_obtainFrames++;
            m_packet->pts = qRound64(m_obtainFrames * (qreal(m_totalTime) / m_totalFrames));
#endif

            // int ret = avcodec_send_packet()
        }
    }
}

void VideoDecode::close()
{

}

bool VideoDecode::isEnd()
{

}

const qint64 &VideoDecode::pts()
{

}
