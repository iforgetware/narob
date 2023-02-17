TEMPLATE = subdirs

INCLUDEPATH += .
DEPENDPATH += .

SUBDIRS += \
    narob-core \
    narob-desktop

DISTFILES += \
    README \
    notes.txt

narob-desktop.depends = narob-core
