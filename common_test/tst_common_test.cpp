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
    void test_logging_2();
    QString readOneLine(const char *filename);
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

QString common_test::readOneLine(const char *filename) {
    QScopedPointer<QFile> file;
    file.reset(new QFile(filename));
    if (file.data()->open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(file.data());
        if (!in.atEnd()) {
            auto line = in.readLine();
            return(line);
        }
    }
    return(QString(""));
}

void common_test::test_logging_1()  {
    esi::initlog("testapp.log", true);
    esi::setLogLevel(LEVEL_INFO);

    qInfo() << "testApp begin to run...";
    QString s = readOneLine("testapp.log");
    QVERIFY(s == "[Info] testApp begin to run...");
}

void common_test::test_logging_2()  {
    esi::initlog("testapp.log", true);
    esi::setLogLevel(LEVEL_DEBUG);

    qDebug() << "testApp begin to run...";
    QString s = readOneLine("testapp.log");
    QVERIFY(s == "[Debug] testApp begin to run...");
}

QTEST_APPLESS_MAIN(common_test)

#include "tst_common_test.moc"

