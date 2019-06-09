TEMPLATE = lib
QT += sql xlsx
CONFIG += c++14

HEADERS += \
    Database.h \
    ReportManager.h \
    Parser.h \
    IsbParser.h \
    TitanParser.h \
    OrdinaryParser.h \
    AppName.h \
    SplitDatabaseMessage.h \
    Query.h \
    QueryOrdinary.h \
    TitanQuery.h \
    IsbQuery.h \
    UiController.h \
    Report.h \
    OrdinaryReport.h \
    TitanReport.h \
    IsbReport.h \
    Properties.h \
    ReportWriter.h

SOURCES += \
    Database.cpp \
    ReportManager.cpp \
    IsbParser.cpp \
    TitanParser.cpp \
    OrdinaryParser.cpp \
    SplitDatabaseMessage.cpp \
    QueryOrdinary.cpp \
    TitanQuery.cpp \
    AppName.cpp \
    IsbQuery.cpp \
    UiController.cpp \
    OrdinaryReport.cpp \
    TitanReport.cpp \
    IsbReport.cpp \
    Properties.cpp \
    ReportWriter.cpp

LIBS += -lboost_filesystem -lboost_system

RESOURCES +=

