#ifndef PROCESS_H
#define PROCESS_H

#include "global.h"
#include <QString>

BEGIN_NAMESPACE_ESI

void signalHandler(int sig);
void initDaemon(const QString &runningDir, const QString &lockFile);

END_NAMESPACE_ESI

#endif // PROCESS_H
