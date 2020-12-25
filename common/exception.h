#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "global.h"
#include <QException>

BEGIN_NAMESPACE_ESI

class Exception : public QException
{
public:
    explicit Exception(const char *errorString);
    explicit Exception(const QString &errorString);
    explicit Exception(int errorCode, const char *errorString = nullptr);
    explicit Exception(int errorCode, const QString &errorString);

    Exception(const Exception &copy);

    ~Exception() override;

    int errorCode() const;
    QString errorString() const;

    void raise() const override;
    Exception *clone() const override;

protected:
    int m_errorCode;
    QString m_errorString;
};

END_NAMESPACE_ESI

#endif // EXCEPTION_H
