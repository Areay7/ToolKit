#include "xlsxmanager.h"
#include <QProcess>
#include <QDir>
#include <QDebug>

XlsxManager::XlsxManager()
{
    m_xlsx = new QXlsx::Document("AAAA", this);
}

XlsxManager::~XlsxManager()
{

}

bool XlsxManager::openOffice()
{
    bool ret = false;
#ifdef WINDOWS_SPECIFIC_DEFINE
    ret = QProcess::startDetached("C:/Program Files/Microsoft Office/root/Office16/EXCEL.EXE",
                                       QStringList() << QDir::currentPath() + "/" + "");
#endif

#ifdef MAC_SPECIFIC_DEFINE
    ret = QProcess::startDetached("/Applications/Microsoft Excel.app/Contents/MacOS/Microsoft Excel",
                                       QStringList() << QDir::currentPath() + "/" + "");
#endif
    if(!ret)
    {
        qWarning() << "Open Excel Fail !";
    }
    return ret;
}


