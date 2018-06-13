TEMPLATE = subdirs

SUBDIRS += \
    lottie-qt \
    examples

examples.depends = lottie-qt

OTHER_FILES += \
    lottie-qt.pri
