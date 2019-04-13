include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
    ../interfaces/compression.h \
        tst_compress16.h \
    tst_compress12.h \
    ../CompressionSrc/ibuffer.h \
    ../src/compress12.h \
    ../sharedmocks/ibuffermock.h

SOURCES += \
        main.cpp \
    ../src/compress12.cpp

INCLUDEPATH += ../src
INCLUDEPATH += ../interfaces
INCLUDEPATH += ../sharedmocks
