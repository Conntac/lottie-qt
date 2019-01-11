LOTTIE_DIR = $$PWD/lottie_qt/Classes

CONFIG += link_prl

INCLUDEPATH += $$LOTTIE_DIR

LIBS += -L$$shadowed($$PWD/lottie_qt) -llottie_qt

PRE_TARGETDEPS += $$shadowed($$PWD/lottie_qt)/liblottie_qt.a

QML_IMPORT_PATH += $$PWD/lottie_qt

