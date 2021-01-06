#include <QCoreApplication>
#include <QCommandLineParser>
#include <memory>
#include <QDebug>
#include <QTimer>
#include "global.h"
#include "logging.h"
#include "options.h"
#include "process.h"
#include "sharedmemory.h"
#include "exception.h"
#include <unistd.h>
#include <iostream>

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

struct Application {
    QString m_name;
    QString m_command;
    QStringList m_args;
};

void startProcesses() {
    QVector<Application> appList;
    appList.append(Application{"us", "us", QStringList() << "-l" << "5" << "-o" << "us.log"});
    appList.append(Application{"img", "img", QStringList() << "-l" << "5" << "-o" << "img.log"});

    for (auto &app : appList) {
        HostProcess *p = new HostProcess(app.m_name);
        p->setWorkingDirectory(QCoreApplication::applicationDirPath());
        p->start(app.m_command, app.m_args);
        processList.append(p);
    }
}

int main(int argc, char *argv[]) {
    initDaemon(get_current_dir_name(), "mgr.pid");

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("mgr");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Manager");
    handleCommandlineOptions(app, parser);
    qInfo() << QCoreApplication::applicationName() << "Begin to run...";

    SharedMemoryForImage shm;
    shm.create(SharedMemoryForImage::SIZE);

    startProcesses();

    return app.exec();
}
