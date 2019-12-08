TEMPLATE = lib
QT += sql xlsx
CONFIG += c++14

HEADERS += \
    Database.h \
    ReportManager.h \
    Parser.h \
    Query.h \
    UiController.h \
    Report.h \
    OrdinaryReport.h \
    Properties.h \
    ReportWriter.h \
    ConfigReader.h \
    ConfiguredParser.h \
    Configuration.h \
    DocumentProperties.h \
    OrdinaryQuery.h \
    OrdinaryParser.h

SOURCES += \
    Database.cpp \
    ReportManager.cpp \
    UiController.cpp \
    OrdinaryReport.cpp \
    Properties.cpp \
    ReportWriter.cpp \
    ConfigReader.cpp \
    ConfiguredParser.cpp \
    OrdinaryQuery.cpp \
    OrdinaryParser.cpp

LIBS += -lboost_filesystem -lboost_system

RESOURCES +=

