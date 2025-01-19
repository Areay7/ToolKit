#ifndef XLSXMANAGER_H
#define XLSXMANAGER_H

#include <QObject>
#include "xlsxdocument.h"


class XlsxManager : QObject
{
    Q_OBJECT

public:
    XlsxManager();
    ~XlsxManager();

    bool openOffice();

private:
    QXlsx::Document *m_xlsx = nullptr;
};

#endif // XLSXMANAGER_H
