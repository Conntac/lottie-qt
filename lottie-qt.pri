LOTTIE_DIR = $$PWD/lottie-qt/Classes

CONFIG += link_prl

INCLUDEPATH += $$LOTTIE_DIR

LIBS += -L$$shadowed($$PWD/lottie-qt) -llottie-qt

#PRE_TARGETDEPS += -L$$shadowed($$PWD/lottie-qt)/liblottie-qt.a
