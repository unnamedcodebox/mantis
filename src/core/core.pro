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
    ReportWriter.h \
    ConfigReader.h \
    ConfiguredParser.h \
    Configuration.h \
    OrdinaryParserNew.h \
    DocumentProperties.h \
    OrdinaryQuery.h

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
    ReportWriter.cpp \
    ConfigReader.cpp \
    ConfiguredParser.cpp \
    OrdinaryParserNew.cpp \
    OrdinaryQuery.cpp

LIBS += -lboost_filesystem -lboost_system

RESOURCES +=

