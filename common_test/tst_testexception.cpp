#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "exception.h"

class testException : public QObject
{
    Q_OBJECT

public:
    testException();
    ~testException();

private slots:
    void test_case1();

};

testException::testException()
{

}

testException::~testException()
{

}

void testException::test_case1()
{
    try {
        throw esi::Exception(1, "Test Exception.");
    } catch (esi::Exception &e) {
        QVERIFY(e.errorCode() == 1);
        QVERIFY(e.errorString() == QString("Test Exception."));
    }
}

QTEST_MAIN(testException)

#include "tst_testexception.moc"
