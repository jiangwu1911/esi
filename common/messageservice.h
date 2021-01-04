#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <QString>
#include <QObject>
#include <QtDBus/QtDBus>
#include "common_global.h"
#include "global.h"

BEGIN_NAMESPACE_ESI

class COMMON_EXPORT MessageService {
public:
    MessageService(const QString &name, QObject *obj);
private:
    QString m_name;
};


END_NAMESPACE_ESI

#endif // MESSAGESERVICE_H
