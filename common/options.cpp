#include "global.h"
#include "logging.h"
#include "options.h"

BEGIN_NAMESPACE_ESI

void setCommonOptions(QCommandLineParser &parser) {
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(logLevelOption);
    parser.addOption(logFileOption);
}

void processCommonOptions(QCommandLineParser &parser) {
    QString logFilename = QCoreApplication::applicationName() + ".log";
    if (parser.isSet(logFileOption)) {
        logFilename = parser.value(logFileOption);
    }
    initlog(logFilename);

    int logLevel = LEVEL_INFO;
    if (parser.isSet(logLevelOption)) {
        logLevel = parser.value(logLevelOption).toInt();
    }
    setLogLevel(logLevel);
}

END_NAMESPACE_ESI
