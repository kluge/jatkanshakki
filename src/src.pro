TEMPLATE = lib

TARGET = jatkanshakki

QT += qml quick

CONFIG += c++11

SOURCES += Game.cpp \
  Opponent.cpp \
  Board.cpp

HEADERS += \
  Game.h \
  Opponent.h \
  Board.h
