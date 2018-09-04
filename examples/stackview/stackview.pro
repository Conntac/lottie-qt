TEMPLATE = app

QT += quick quickcontrols2

#QMAKE_XCODE_LIBRARY_SUFFIX_SETTING =

SOURCES += \
    main.cpp

RESOURCES += \
    qml.qrc \
    ../tests/tests.qrc

include(../../lottie-qt.pri)
