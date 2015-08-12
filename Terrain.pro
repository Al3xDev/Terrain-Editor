#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T21:48:43
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Terrain
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    glwidget.cpp

HEADERS  += widget.h \
    glwidget.h \
    Terrain.h \
    Shader.h

FORMS    += widget.ui

LIBS += -L/path/to/glew/lib -lGLEW -lGLU -lGL -lSOIL


