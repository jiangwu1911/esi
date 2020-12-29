#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include "global.h"
#include "logging.h"
#include "options.h"
#include "process.h"

USE_NAMESPACE_ESI

void setMgrOptions(__attribute__((unused)) QCommandLineParser &parser) {
}

void processMgrOptions(__attribute__((unused)) QCommandLineParser &parser) {
}

void handleCommandlineOptions(QCoreApplication &app, QCommandLineParser &parser) {
    setCommonOptions(parser);
    setMgrOptions(parser);

    parser.process(app);

    processCommonOptions(parser);
    processMgrOptions(parser);
}

void initApplications() {

}

int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("mgr");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Manager");

    handleCommandlineOptions(app, parser);

    qInfo() << QCoreApplication::applicationName() << "begin to run...";

    initDaemon(QCoreApplication::applicationDirPath(), QCoreApplication::applicationName() + ".pid");
    return 0;
}
