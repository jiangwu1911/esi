#ifndef PROCESS_H
#define PROCESS_H

#include "global.h"
#include "common_global.h"
#include <QString>
#include <QObject>
#include <QProcessEnvironment>

BEGIN_NAMESPACE_ESI

void signalHandler(int sig);
void initDaemon(const QString &runningDir, const QString &lockFile);

class COMMON_EXPORT HostProcess : public QObject {
    Q_OBJECT

public:
    HostProcess(const QString &name);
    ~HostProcess();

    qint64 processId();
    QProcess::ProcessState state();

    void setWorkingDirectory(const QString &dir);
    void setProcessEnvironment(const QProcessEnvironment &environment);

public slots:
    void kill();
    void terminate();
    void start(const QString &program, const QStringList &arguments);

private:
    QString m_name;
    QProcess *m_process;
    qint64 m_pid = 0;
    QProcess::ProcessError m_error;
    int m_exitCode;
    QProcess::ExitStatus m_exitStatus;
    QProcess::ProcessState m_state;
};

END_NAMESPACE_ESI

#endif // PROCESS_H
