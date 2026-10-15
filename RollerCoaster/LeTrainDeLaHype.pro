TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -pthread

SOURCES += \
        train.cpp \
        main.cpp \
        voyageur.cpp

HEADERS += \
    train.h \
    voyageur.h
