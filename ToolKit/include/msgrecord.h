#ifndef MSGRECORD_H
#define MSGRECORD_H

#include <QWidget>
#include <msgrecord.h>

namespace Ui {
class MsgRecord;
}

class MsgRecord : public QWidget
{
    Q_OBJECT

public:
    explicit MsgRecord(QWidget *parent = nullptr);
    ~MsgRecord();

private:
    Ui::MsgRecord *ui;
};

#endif // MSGRECORD_H
