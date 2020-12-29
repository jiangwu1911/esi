#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QCommandLineOption>
#include <QCommandLineParser>
#include "global.h"

BEGIN_NAMESPACE_ESI

const QCommandLineOption logLevelOption(QStringList() << "l" << "loglevel",
                                        "The log level: \n 5: debug\n 4: info: \n 3: warning\n 2: critical \n 1: fatal",
                                        "loglevel");
const QCommandLineOption logFileOption(QStringList() << "o" << "logfile",
                                       "The log file name.",
                                       "logfile");

void setCommonOptions(QCommandLineParser &parser);
void processCommonOptions(QCommandLineParser &parser);

END_NAMESPACE_ESI

#endif // OPTIONS_HPP
