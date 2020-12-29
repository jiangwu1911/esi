#include "application.h"

BEGIN_NAMESPACE_ESI

EsiApplication::EsiApplication(const int id, const QString &name, const QString &command, const QString &parameters)
    : m_id(id), m_name(name), m_command(command), m_parameters(parameters) {
    m_state = NotRunning;
}

END_NAMESPACE_ESI
