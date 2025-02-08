#ifndef READTHREAD_H
#define READTHREAD_H

#include <QElapsedTimer>
#include <QThread>

class VideoDecode;

class ReadThread : public QThread
{
    Q_OBJECT

public:
    explicit ReadThread(QObject *parent = nullptr);
    ~ReadThread() override;

    enum PlayState
    {
        play,
        end
    };

    void open(const QString &url = QString());
    void pause(bool flag);
    void close();
    const QString &url();

protected:
    void run() override;

signals:
    void updateImage(const QImage &image);
    void playState(PlayState state);

private:
    VideoDecode *m_videoDecode = nullptr;
    QString m_url;
    bool m_play = false;
    bool m_pause = false;
    QElapsedTimer m_etime1;
    QElapsedTimer m_etime2;
};

#endif
