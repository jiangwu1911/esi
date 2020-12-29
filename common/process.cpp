#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <QDebug>
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

END_NAMESPACE_ESI
