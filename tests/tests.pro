TEMPLATE = app
TARGET = mantis_tests
QT += sql xlsx core

DEPENDPATH += . ../src/core ../src/config
INCLUDEPATH += ../src/core ../src/config
LIBS += -L../src/core/ -lcore -lgtest -L../src/config/ -lconfig

SOURCES += \
    main.cpp \
    ParserTests.cpp \
    DatabaseTests.cpp \
    ConfigFromFileTests.cpp \
    TimeReportTests.cpp \
    QueryTests.cpp

copydata.commands = $(COPY_DIR) $$PWD/config.json $$PWD/device_list.json $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
