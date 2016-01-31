TEMPLATE = app

QT += testlib

CONFIG += c++11

SOURCES += main.cpp

INCLUDEPATH += ../src

LIBS += -L../src -ljatkanshakki
