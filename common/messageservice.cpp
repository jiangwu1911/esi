#include "messageservice.h"
#include "exception.h"
#include <QtDBus/QtDBus>
#include <QDebug>

BEGIN_NAMESPACE_ESI

MessageService::MessageService(const QString &name, QObject *obj) :
    m_name{name} {

    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerService(m_name)) {
        throw Exception(QDBusConnection::sessionBus().lastError().message());
    }
    QDBusConnection::sessionBus().registerObject("/", obj, QDBusConnection::ExportAllSlots);
    qDebug() << "D-Bus service" << m_name << "registed.";
}

END_NAMESPACE_ESI
