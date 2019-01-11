TEMPLATE = subdirs

SUBDIRS += \
    lottie_qt \
    examples

examples.depends = lottie_qt

OTHER_FILES += \
    lottie-qt.pri
