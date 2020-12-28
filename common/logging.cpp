#include <QTextStream>
#include <iostream>
#include <memory>
#include "global.h"
#include "logging.h"

BEGIN_NAMESPACE_ESI

void initlog(const QString &filename) {
    m_logFile.reset(new QFile(filename));
    m_logFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);
}

void messageHandler(QtMsgType type, __attribute__((unused)) const QMessageLogContext &context, const QString &message) {
    QString levelText;
    switch (type) {
        case QtDebugMsg:
            levelText = "Debug";
            break;
        case QtInfoMsg:
            levelText = "Info";
            break;
        case QtWarningMsg:
            levelText = "Warning";
            break;
        case QtCriticalMsg:
            levelText = "Critical";
            break;
        case QtFatalMsg:
            levelText = "Fatal";
            break;
    }

    QString text = QString("[%1] %2").arg(levelText);
    text = text.arg(message);
    QTextStream out(m_logFile.data());
    out << text << Qt::endl;
}

END_NAMESPACE_ESI
