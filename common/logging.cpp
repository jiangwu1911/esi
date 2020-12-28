#include <QTextStream>
#include <iostream>
#include <memory>
#include "global.h"
#include "logging.h"

BEGIN_NAMESPACE_ESI

void initlog(const QString &filename, const bool clearOldLogs) {
    m_logFile.reset(new QFile(filename));
    if (clearOldLogs == true) {
        m_logFile.data()->open(QFile::WriteOnly | QFile::Text);
    } else {
        m_logFile.data()->open(QFile::Append | QFile::Text);
    }
    qInstallMessageHandler(messageHandler);
}

void setLogLevel(int logLevel) {
    m_logLevel = logLevel;
}

void messageHandler(QtMsgType type, __attribute__((unused)) const QMessageLogContext &context, const QString &message) {
    QString levelText;
    int level;

    switch (type) {
        case QtDebugMsg:
            levelText = "Debug";
            level = LEVEL_DEBUG;
            break;
        case QtInfoMsg:
            levelText = "Info";
            level = LEVEL_INFO;
            break;
        case QtWarningMsg:
            levelText = "Warning";
            level = LEVEL_WARNING;
            break;
        case QtCriticalMsg:
            levelText = "Critical";
            level = LEVEL_CRITICAL;
            break;
        case QtFatalMsg:
            levelText = "Fatal";
            level = LEVEL_FATAL;
            break;
    }

    if (level <= m_logLevel) {
        QString text = QString("[%1] %2").arg(levelText);
        text = text.arg(message);
        QTextStream out(m_logFile.data());
        out << text << Qt::endl;
    }
}

END_NAMESPACE_ESI
