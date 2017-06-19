android|ios|tvos|winrt {
    warning( "This example is not supported for android, ios, tvos, or winrt." )
}

!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

QMAKE_CXXFLAGS += -std=c++11

QT += 3dcore 3drender 3dinput 3dextras
QT += widgets

SOURCES += main.cpp \
    scenemodifier.cpp

HEADERS += \
    scenemodifier.h \
    kohonen.h

DISTFILES += \
    datos.txt


