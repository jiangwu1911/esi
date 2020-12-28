#include <QtTest>
#include <iostream>
#include "global.h"
#include "exception.h"
#include "logging.h"

// add necessary includes here

class common_test : public QObject {
    Q_OBJECT

public:
    common_test();
    ~common_test();

private slots:
    void test_exception_1();
    void test_logging_1();

};

common_test::common_test() {
}

common_test::~common_test() {
}

void common_test::test_exception_1() {
    try {
        throw esi::Exception(1, "Test Exception.");
    } catch (esi::Exception &e) {
        QVERIFY(e.errorCode() == 1);
        QVERIFY(e.errorString() == QString("Test Exception."));
    }
}

void common_test::test_logging_1()  {
    esi::initlog("testapp.log");
    qDebug() << "testApp begin to run...";

    QScopedPointer<QFile> file;
    file.reset(new QFile("testapp.log"));
    if (file.data()->open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(file.data());
        if (!in.atEnd()) {
            QString line = in.readLine();
            QVERIFY(line == "[Debug] testApp begin to run...");
            return;
        }
    }
    QFAIL("Write log failed.");
}

QTEST_APPLESS_MAIN(common_test)

#include "tst_common_test.moc"

