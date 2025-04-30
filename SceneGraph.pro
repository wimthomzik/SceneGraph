#-------------------------------------------------
#
# Project created by QtCreator 2025-04-10T09:02:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SceneGraph
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        boundingboxdrawvisitor.cpp \
        circle.cpp \
        cullingvisitor.cpp \
        geode.cpp \
        group.cpp \
        main.cpp \
        dialog.cpp \
        canvas.cpp \
        node.cpp \
        nodevisitor.cpp \
        pickingvisitor.cpp \
        polygon.cpp \
        sceneeditor.cpp \
        scenerenderer.cpp \
        transform.cpp

HEADERS += \
        boundingboxdrawvisitor.h \
        circle.h \
        cullingvisitor.h \
        dialog.h \
        canvas.h \
        geode.h \
        group.h \
        node.h \
        nodevisitor.h \
        pickingvisitor.h \
        polygon.h \
        sceneeditor.h \
        scenerenderer.h \
        transform.h \
        vec2.h

FORMS += \
        dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
