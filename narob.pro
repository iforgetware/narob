TEMPLATE = subdirs

INCLUDEPATH += .
DEPENDPATH += .

SUBDIRS += \
    narob-core \
    narob-desktop

narob-desktop.depends = narob-core
