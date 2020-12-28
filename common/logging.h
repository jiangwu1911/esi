#ifndef LOGGING_H
#define LOGGING_H

#include <QString>
#include <QFile>
#include "global.h"

BEGIN_NAMESPACE_ESI

static QScopedPointer<QFile> m_logFile;

void initlog(const QString &logfile);
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &message);

END_NAMESPACE_ESI

#endif // LOGGING_H


