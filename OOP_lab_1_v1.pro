TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        exceptions.cpp \
        main.cpp \
        test.cpp

HEADERS += \
    exceptions.h \
    iterator.h \
    matrix.h \
    test.h
