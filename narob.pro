TEMPLATE = subdirs

INCLUDEPATH += .
DEPENDPATH += .

SUBDIRS += \
    narob-core \
    narob-desktop

DISTFILES += \
    README

narob-desktop.depends = narob-core
