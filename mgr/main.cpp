#include <QCoreApplication>
#include <QCommandLineParser>
#include "global.h"
#include "logging.h"

USE_NAMESPACE_ESI

const QCommandLineOption logLevelOption("l", "The log level.", "loglevel");

void initOptions(QCommandLineParser &parser) {

    parser.setApplicationDescription("Manager");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(logLevelOption);
}

int main(int argc, char *argv[]) {
    QCommandLineParser parser;

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("mgr");
    QCoreApplication::setApplicationVersion("0.1");

    initOptions(parser);
    parser.process(app);

    if (parser.isSet(logLevelOption)) {
        const QString param = parser.value(logLevelOption);
        setLogLevel(param.toInt());
    }
    initlog("mgr.log");

    return app.exec();
}
