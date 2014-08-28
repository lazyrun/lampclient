TEMPLATE = app
DESTDIR = bin
TARGET = LampClient

CONFIG += debug_and_release
QT += network

INCLUDEPATH  += . gui
DEPENDPATH   += . gui

# Input
HEADERS += $$files(gui/*.h) \
           $$files(*.h)

SOURCES += $$files(gui/*.cpp) \
           $$files(*.cpp)

