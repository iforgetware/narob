TEMPLATE = subdirs

SUBDIRS += \
    narob-core \
    narob-desktop

narob-desktop.depends = narob-core
