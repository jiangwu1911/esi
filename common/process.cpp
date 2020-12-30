#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <QDebug>
#include <QThread>
#include "global.h"
#include "logging.h"
#include "process.h"

BEGIN_NAMESPACE_ESI

void signalHandler(int sig) {
    switch(sig) {
        case SIGHUP:
            qInfo() << "hangup signal catched";
            break;
        case SIGTERM:
            qInfo() << "terminate signal catched";
            break;
    }
}

void initDaemon(const QString &runningDir, const QString &lockFile) {
    int i, lfp;
    char str[10];

    if(getppid() == 1) {
        return;    /* already a daemon */
    }

    i = fork();
    if (i < 0) {
        exit(1);    /* fork error */
    }
    if (i > 0) {
        exit(0);    /* parent exits */
    }

    /* child (daemon) continues */
    setsid(); /* obtain a new process group */

    for (i = getdtablesize(); i >= 0; --i) {
        close(i);    /* close all descriptors */
    }

    i = open("/dev/null", O_RDWR);
    dup(i);
    dup(i); /* handle standart I/O */

    umask(027); /* set newly created file permissions */

    chdir(runningDir.toLatin1()); /* change running directory */
    lfp = open(lockFile.toLatin1(), O_RDWR | O_CREAT, 0640);
    if (lfp < 0) {
        exit(1);    /* can not open */
    }
    if (lockf(lfp, F_TLOCK, 0) < 0) {
        exit(0);    /* can not lock */
    }

    /* first instance continues */
    sprintf(str, "%d\n", getpid());
    write(lfp, str, strlen(str)); /* record pid to lockfile */
    signal(SIGCHLD, SIG_IGN); /* ignore child */
    signal(SIGTSTP, SIG_IGN); /* ignore tty signals */
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGHUP, signalHandler); /* catch hangup signal */
    signal(SIGTERM, signalHandler); /* catch kill signal */
}

HostProcess::HostProcess(const QString &name)
    : m_name(name) {
    m_process = new QProcess(this);
    m_process->setProcessChannelMode(QProcess::MergedChannels);
}

HostProcess::~HostProcess() {
    delete m_process;
}

qint64 HostProcess::processId() {
    return m_pid;
}

QProcess::ProcessState HostProcess::state() {
    return m_state;
}

void HostProcess::start(const QString &program, const QStringList &arguments) {
    connect(m_process, &QProcess::started, this, [this]() {
        // we to cache the pid in order to have it available after the process crashed
        m_pid = m_process->processId();
        qDebug() << "Process" << m_name << "started, pid is" << m_pid;
    });
    connect(m_process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        m_error = error;
        qDebug() << m_name << "error occurred," << m_error;
    });
    connect(m_process, static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
    this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
        m_exitCode = exitCode;
        m_exitStatus = exitStatus;
        qDebug() << "Process" << m_name << "exist," << m_exitCode << " " << m_exitStatus;
    });
    connect(m_process, &QProcess::stateChanged,
    this, [this](QProcess::ProcessState newState) {
        m_state = newState;
        qDebug() << "Process" << m_name << "state changed to" << m_state;
    });

    qInfo() << "Try to start sub process: " << program << " " << arguments;
    m_process->start(program, arguments);
}

void HostProcess::setWorkingDirectory(const QString &dir) {
    m_process->setWorkingDirectory(dir);
}

void HostProcess::setProcessEnvironment(const QProcessEnvironment &environment) {
    m_process->setProcessEnvironment(environment);
}

void HostProcess::kill() {
    m_process->kill();
}

void HostProcess::terminate() {
    m_process->terminate();
}

END_NAMESPACE_ESI
