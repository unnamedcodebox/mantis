TEMPLATE = subdirs

SUBDIRS += \
    app \
    core \
    tests

core.subdir = src/core
core.target = sub-src-core
app.subdir = src/app

app.depends = core
tests.depends = core
