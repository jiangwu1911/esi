QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../common/exception.cpp

HEADERS += \
    ../common/common_global.h \
    ../common/exception.h \
    ../common/global.h

SOURCES +=  tst_testexception.cpp

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
