#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <msgrecord.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWheelEvent>
#include <QList>

#include "commonutils.h"
#include "commonbase.h"
#include "xlsxmanager.h"
#include "readthread.h"
#include "playimage.h"

class MsgRecord;

namespace Ui {
class MainPage;
}


class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();


protected:
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void switchStatckPage();
    void onWidgetClicked(MsgRecord *msgRecord);

    // VideoPlay
    void selectFileToPlay();
    void openClick();
    void pauseClick();
    void on_playState(ReadThread::PlayState state);
    // End of VideoPlay

private:
    void updateVisibleWidgets();
    void free();
    void setPicture();

private:
    Ui::MainPage *ui;
    QScrollArea *m_scrollArea;
    QWidget *m_containerWidget;
    QVBoxLayout *m_containerLayout;
    QList<MsgRecord *> m_widgetList;
    MsgRecord *m_lastSelectedWidget;
    int m_visibleStartIndex;

    XlsxManager *m_xlsx;

    // VideoPlay
    ReadThread *m_readThread = nullptr;
    bool m_isPlay;
    // End of VideoPlay


};

#endif // MAINPAGE_H
