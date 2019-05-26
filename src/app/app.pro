TEMPLATE = app
TARGET = mantis

QT += quick core sql
CONFIG += c++14

DEPENDPATH += ../config ../core
INCLUDEPATH += ../config ../core
LIBS += -L../core/ -lcore -lboost_filesystem -lboost_system -L../config/ -lconfig

SOURCES += \
        main.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

copydata.commands = $(COPY_DIR) $$PWD/device_list.json $$PWD/config.json $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
