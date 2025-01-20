#include "videodecode.h"
#include "readthread.h"

#include <QEventLoop>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>
#include <qimage.h>

ReadThread::ReadThread(QObject *parent) : QThread(parent)
{
   m_videoDecode = new VideoDecode();

   qRegisterMetaType<PlayState>("PlayState"); 
}

ReadThread::~ReadThread()
{
    if(m_videoDecode)
    {
        delete m_videoDecode;
    }
}

void ReadThread::open(const QString &url)
{
    if(!this->isRunning())
    {
        m_url = url;
        emit this->start();
    }
} 

void ReadThread::pause(bool flag)
{
    m_pause = flag;
}

void ReadThread::close()
{
    m_play = false;
    m_pause = false;
}

const QString &ReadThread::url()
{
    return m_url;
}

void sleepMsec(int msec)
{
    if(msec <= 0) return;
    QEventLoop loop;
    QTimer::singleShot(msec, &loop, SLOT(quit()));
    loop.exec();
}

void ReadThread::run()
{
    bool ret = m_videoDecode->open(m_url);
    if(ret)
    {
        m_play = true;
        m_etime1.restart();
        m_etime2.restart();
        emit playState(play);
    }
    else
    {
        qWarning() << "open fail";
    }

    while(m_play)
    {
        while(m_pause)
        {
            sleepMsec(200);
        }

        QImage image = m_videoDecode->read();
        if(!image.isNull())
        {
#if 0
            sleepMsec(int(m_decodeVideo->pts() - m_etime1.elapsed()));
#else
            sleepMsec(int(m_videoDecode->pts() - m_etime2.elapsed()));
#endif
            emit updateImage(image);
        }
        else
        {
            if(m_videoDecode->isEnd())
            {
                break;
            }
            sleepMsec(1);
        }
    }

    qDebug() << "play over !";
    m_videoDecode->close();
    emit playState(end);
}