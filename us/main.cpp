#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include "global.h"
#include "options.h"

USE_NAMESPACE_ESI

void setUsOptions(__attribute__((unused)) QCommandLineParser &parser) {
}

void processUsOptions(__attribute__((unused)) QCommandLineParser &parser) {
}

void handleCommandlineOptions(QCoreApplication &app, QCommandLineParser &parser) {
    setCommonOptions(parser);
    setUsOptions(parser);

    parser.process(app);

    processCommonOptions(parser);
    processUsOptions(parser);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("us");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("UltraSound");
    handleCommandlineOptions(app, parser);

    qInfo() << QCoreApplication::applicationName() << "begin to run...";

    MainWindow w;
    w.setWindowTitle(QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion());
    w.show();
    return app.exec();
}
