TEMPLATE = lib
CONFIG += c++14

LIBS += -lboost_filesystem -lboost_system

HEADERS += \
    ConfigReader.h

SOURCES += \
    ConfigReader.cpp
