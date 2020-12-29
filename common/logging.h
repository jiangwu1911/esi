#ifndef LOGGING_H
#define LOGGING_H

#include <QString>
#include <QFile>
#include "global.h"

BEGIN_NAMESPACE_ESI

#define LEVEL_DEBUG 5
#define LEVEL_INFO 4
#define LEVEL_WARNING 3
#define LEVEL_CRITICAL 2
#define LEVEL_FATAL 1

static int m_logLevel = LEVEL_INFO;    // qDebug will not write log file by default
static QScopedPointer<QFile> m_logFile;

void initlog(const QString &logfile, const bool clearOldLogs=false);
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);
void setLogLevel(int logLevel);

END_NAMESPACE_ESI

#endif // LOGGING_H


