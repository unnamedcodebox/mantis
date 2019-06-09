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

LANGUAGES = ru

# parameters: var, prepend, append
defineReplace(prependAll) {
 for(a,$$1):result += $$2$${a}$$3
 return($$result)
}

TRANSLATIONS = $$prependAll(LANGUAGES, $$PWD/src/app/mantis_, .ts)
TRANSLATIONS += $$prependAll(LANGUAGES, $$PWD/src/core/core_, .ts)

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
