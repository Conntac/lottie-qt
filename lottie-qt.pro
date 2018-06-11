TEMPLATE = subdirs

SUBDIRS += \
    lottie-qt \
    examples

examples.depends = lottie-qt
