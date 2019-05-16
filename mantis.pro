TEMPLATE = subdirs

SUBDIRS += \
    app \
    core \
    config \
    tests

core.subdir = src/core
core.target = sub-src-core

config.subdir = src/config
config.target = sub-src-config

app.subdir = src/app

app.depends = config core
tests.depends = config core

#QMAKE_LFLAGS += -Wl,-rpath,"'$$ORIGIN'"
