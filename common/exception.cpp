#include "global.h"
#include "exception.h"

BEGIN_NAMESPACE_ESI

Exception::Exception(const char *errorString)
    : m_errorCode(0)
    , m_errorString(errorString)
{ }

Exception::Exception(const QString &errorString)
    : m_errorCode(0)
    , m_errorString(errorString)
{ }

Exception::Exception(int errorCode, const char *errorString)
    : m_errorCode(errorCode)
    , m_errorString(errorString)
{ }

Exception::Exception(int errorCode, const QString &errorString)
    : m_errorCode(errorCode)
    , m_errorString(errorString)
{ }

Exception::Exception(const Exception &copy)
    : m_errorCode(copy.m_errorCode)
    , m_errorString(copy.m_errorString)
{ }

Exception::~Exception()
{ }

int Exception::errorCode() const {
    return m_errorCode;
}

QString Exception::errorString() const {
    return m_errorString;
}

void Exception::raise() const {
    throw *this;
}

Exception *Exception::clone() const {
    return new Exception(*this);
}

END_NAMESPACE_ESI
