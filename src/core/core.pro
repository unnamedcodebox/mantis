TEMPLATE = lib
QT += sql
CONFIG += c++14

HEADERS += \
    Database.h \
    ReportManager.h \
    Parser.h \
    IsbParser.h \
    TitanParser.h \
    OrdinaryParser.h \
    AppName.h \
    SplitDatabaseMessage.h

SOURCES += \
    Database.cpp \
    ReportManager.cpp \
    IsbParser.cpp \
    TitanParser.cpp \
    OrdinaryParser.cpp \
    SplitDatabaseMessage.cpp

LIBS += -lboost_filesystem -lboost_system

RESOURCES +=

