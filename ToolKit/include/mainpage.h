#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <msgrecord.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWheelEvent>
#include <QList>

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
    void SwitchStatckPage();
    void onWidgetClicked(MsgRecord *msgRecord);

private:
    void updateVisibleWidgets();

private:
    Ui::MainPage *ui;
    QScrollArea *m_scrollArea;
    QWidget *m_containerWidget;
    QVBoxLayout *m_containerLayout;
    QList<MsgRecord *> m_widgetList;
    MsgRecord *m_lastSelectedWidget;
    int m_visibleStartIndex;
};

#endif // MAINPAGE_H
