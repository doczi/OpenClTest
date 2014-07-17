TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle qt

SOURCES += \
    main.cpp \
    clinfogatherer.cpp

HEADERS += \
    clinfogatherer.h \
    clinfo.h

INCLUDEPATH += \
    /opt/AMDAPP/include

LIBS += \
    -L/opt/AMDAPP/lib/x86_64 \
    -lOpenCL

QMAKE_CXXFLAGS += -std=c++11
