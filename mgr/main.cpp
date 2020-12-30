#include <QCoreApplication>
#include <QCommandLineParser>
#include <memory>
#include <QDebug>
#include <QTimer>
#include "global.h"
#include "logging.h"
#include "options.h"
#include "process.h"
#include <unistd.h>

USE_NAMESPACE_ESI

QVector<HostProcess *> processList;

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

void startUsProcess() {
    HostProcess *usProcess = new HostProcess("us");
    usProcess->setWorkingDirectory(QCoreApplication::applicationDirPath());

    QString command = "us";
    QStringList args;
    args << "-l" << "5"
         << "-o" << "us.log";
    usProcess->start(command, args);
    processList.append(usProcess);
}

void startTestProcess() {
    HostProcess *testProcess = new HostProcess("test");
    testProcess->setWorkingDirectory(QCoreApplication::applicationDirPath());

    QString command = "ls";
    QStringList args;
    args << "-l";
    testProcess->start(command, args);
    processList.append(testProcess);
}

void startProcesses() {
    startTestProcess();
    startUsProcess();
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    initDaemon(QCoreApplication::applicationDirPath(), QCoreApplication::applicationName() + ".pid");

    QCoreApplication::setApplicationName("mgr");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Manager");
    handleCommandlineOptions(app, parser);

    qInfo() << QCoreApplication::applicationName() << "begin to run...";

    startProcesses();

    return app.exec();
}
