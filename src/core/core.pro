TEMPLATE = lib
QT += sql
CONFIG += c++14


LANGUAGES = ru
# parameters: var, prepend, append
defineReplace(prependAll) {
 for(a,$$1):result += $$2$${a}$$3
 return($$result)
}

#TRANSLATIONS += core_ru.ts
TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/core_, .ts)
TRANSLATIONS_FILES =

qtPrepareTool(LRELEASE, lrelease)
for(tsfile, TRANSLATIONS) {
 qmfile = $$shadowed($$tsfile)
 qmfile ~= s,.ts$,.qm,
 qmdir = $$dirname(qmfile)
 !exists($$qmdir) {
 mkpath($$qmdir)|error("Aborting.")
 }
 command = $$LRELEASE -removeidentical $$tsfile -qm $$qmfile
 system($$command)|error("Failed to run: $$command")
 TRANSLATIONS_FILES += $$qmfile
}

HEADERS += \
    Database.h \
    ReportManager.h \
    Parser.h \
    IsbParser.h \
    TitanParser.h \
    OrdinaryParser.h \
    AppName.h \
    SplitDatabaseMessage.h \
    TimeReport.h \
    Query.h \
    QueryOrdinary.h \
    TitanQuery.h \
    IsbQuery.h \
    Watcher.h \
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
    TimeReport.cpp \
    QueryOrdinary.cpp \
    TitanQuery.cpp \
    AppName.cpp \
    IsbQuery.cpp \
    Watcher.cpp \
    OrdinaryReport.cpp \
    TitanReport.cpp \
    IsbReport.cpp \
    Properties.cpp \
    ReportWriter.cpp

LIBS += -lboost_filesystem -lboost_system

RESOURCES +=

copydata.commands = $(COPY_DIR) $$PWD/core_ru.ts $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

