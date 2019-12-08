TEMPLATE = app
TARGET = mantis_tests
QT += sql xlsx core

DEPENDPATH += . ../src/core ../src/config
INCLUDEPATH += ../src/core ../src/config
LIBS += -L../src/core/ -lcore -lgtest

SOURCES += \
    main.cpp \
    ParserTests.cpp \
    DatabaseTests.cpp \
    ConfigFromFileTests.cpp \
    TimeReportTests.cpp \
    QueryTests.cpp \
    ReportWriterTests.cpp \
    OrdinaryParserTests.cpp \
    TitanParserTests.cpp \
    ConfiguredParser.cpp

copydata.commands = $(COPY_DIR) $$PWD/config.json $$PWD/device_list.json $$PWD/isbTests.json $$PWD/test_parsers_configuration $$PWD/configuredParser.json $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

HEADERS += \
    OrdinaryParserTests.h
