TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle qt

SOURCES += \
    main.cpp \
    clinfogatherer.cpp \
    jsonclinfoserializer.cpp \
    openclwrapper.cpp \
    clinfo.cpp

HEADERS += \
    clinfogatherer.h \
    clinfo.h \
    clinfoserializer.h \
    jsonclinfoserializer.h \
    openclwrapper.h

INCLUDEPATH += \
    include \
    /opt/AMDAPP/include

LIBS += \
    -ldl

QMAKE_CXXFLAGS += -std=c++11
