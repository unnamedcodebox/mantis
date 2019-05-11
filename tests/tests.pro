TEMPLATE = app
TARGET = mantis_tests
QT += sql xlsx
DEPENDPATH += . ../src/core
INCLUDEPATH += ../src/core
LIBS += -L../src/core/ -lcore -lgtest

SOURCES += \
    main.cpp \
    ParserTests.cpp \
    DatabaseTests.cpp \
    ConfigFromFileTests.cpp \
    TimeReportTests.cpp

copydata.commands = $(COPY_DIR) $$PWD/config.json $$PWD/device_list.json $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
