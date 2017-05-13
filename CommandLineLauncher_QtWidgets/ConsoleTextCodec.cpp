#include "ConsoleTextCodec.h"

#include <QTextCodec>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

namespace {
QString getConsoleEncoding() {
#ifdef Q_OS_WIN
    return "CP" + QString::number(GetOEMCP());
#else
    return "UTF-8";
#endif  // Q_OS_WIN
}
}  // namespace

QTextCodec* GetConsoleTextCodec() {
    QTextCodec* codec = QTextCodec::codecForName(getConsoleEncoding().toStdString().c_str());
    if (codec)
        return codec;
    return QTextCodec::codecForLocale();
}
