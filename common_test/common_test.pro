QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../common/exception.cpp \
    ../common/logging.cpp \
    ../common/options.cpp \
    ../common/process.cpp \
    tst_common_test.cpp

HEADERS += \
    ../common/common_global.h \
    ../common/exception.h \
    ../common/logging.h \
    ../common/options.h \
    ../common/process.h \
    ../common/global.h

INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common
