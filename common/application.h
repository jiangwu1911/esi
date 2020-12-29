#ifndef APPLICATION_H
#define APPLICATION_H

#include <QString>
#include <QDateTime>
#include "global.h"

BEGIN_NAMESPACE_ESI

class EsiApplication {
public:
    EsiApplication(const int id, const QString &name, const QString &command, const QString &parameters);

    enum State {
        NotRunning,
        StartingUp,
        Running,
        ShuttingDown,
    };

    enum Errors {
        FailedToStart,
        Crashed,
        Timeout,
        UnknownError,
    };

private:
    int m_id;
    QString m_name;
    QString m_command;
    QString m_parameters;
    QDateTime m_startTime;
    State m_state;
    Errors m_error;
};

END_NAMESPACE_ESI

#endif // APPLICATION_H
