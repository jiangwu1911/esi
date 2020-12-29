#include <QTextStream>
#include <iostream>
#include <memory>
#include <QDebug>
#include <QDateTime>
#include "global.h"
#include "logging.h"

BEGIN_NAMESPACE_ESI

void initlog(const QString &filename, const bool clearOldLogs) {
    m_logFile.reset(new QFile(filename));
    bool success = false;

    if (clearOldLogs == true) {
        success = m_logFile.data()->open(QFile::WriteOnly | QFile::Text);
    } else {
        success = m_logFile.data()->open(QFile::Append | QFile::Text);
    }

    if (!success) {
        std::cerr << "Cannot write log file, quit..." << std::endl;
        exit(-1);
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
        QDateTime curDateTime = QDateTime::currentDateTime();

        QString text = QString("%1 [%2] %3");
        text = text.arg(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));
        text = text.arg(levelText);
        text = text.arg(message);
        QTextStream out(m_logFile.data());
        out << text << Qt::endl;
    }
}

END_NAMESPACE_ESI
