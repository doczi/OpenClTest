TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle qt

SOURCES += \
    main.cpp \
    clinfogatherer.cpp \
    openclwrapper.cpp \
    clinfo.cpp \
    openclbinder.cpp \
    xmlserializer.cpp \
    jsonserializer.cpp

HEADERS += \
    clinfogatherer.h \
    clinfo.h \
    openclwrapper.h \
    openclbinder.h \
    openclexception.h \
    xmlserializer.h \
    jsonserializer.h \
    serializer.h

INCLUDEPATH += \
    include \
    /opt/AMDAPP/include

LIBS += \
    -ldl

QMAKE_CXXFLAGS += -std=c++11
