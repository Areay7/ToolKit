#ifndef MSGRECORD_H
#define MSGRECORD_H

#include <QWidget>
#include <msgrecord.h>

const QString default_userName = "User Name333";
const QString default_lastMsg = "Last message";
const QString default_time = "11:30";
const QString default_avatar = ":/res/MainPage/gril.png";

namespace Ui {
class MsgRecord;
}

class MsgRecord : public QWidget
{
    Q_OBJECT

public:
    explicit MsgRecord(const QString &userName = default_userName,  const QString &lastMsg = default_lastMsg,
                       const QString &time = default_time,  const QString &avatarPath = default_avatar, QWidget *parent = nullptr);
    ~MsgRecord();

    void setSelected(bool selected); // 设置控件是否被选中
    bool isSelected() const; // 获取控件是否被选中

signals:
    void clicked(MsgRecord *msgRecord); // 点击信号

protected:
    void mousePressEvent(QMouseEvent *event) override;  // 处理鼠标点击事件

private:
    Ui::MsgRecord *ui;

    QString m_userName;
    QString m_lastMsg;
    QString m_time;
    QString m_avatarPath;

    // QLabel *m_label;
    bool m_selected;


};

#endif // MSGRECORD_H
