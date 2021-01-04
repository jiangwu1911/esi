#QT -= gui
QT += testlib

TEMPLATE = lib
DEFINES += COMMON_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exception.cpp \
    logging.cpp \
    messageservice.cpp \
    options.cpp \
    process.cpp \
    sharedmemory.cpp

HEADERS += \
    common_global.h \
    exception.h \
    global.h \
    logging.h \
    messageservice.h \
    options.h \
    process.h \
    sharedmemory.h

# Default rules for deployment.
unix {
    target.path = /opt/esi/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
