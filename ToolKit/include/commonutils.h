#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QObject>

enum class StackPage : int
{
    ChatPage,
    FriendPage,
    CollectPage,
    MomentsPage,
    ToolPage
};

class CommonUtils : public QObject
{
    Q_OBJECT
public:
    explicit CommonUtils(QObject *parent = nullptr);

public:


signals:
};

template <typename T>
double add(const T &a, const T &b)
{
    return a + b;
}
#endif // COMMONUTILS_H
