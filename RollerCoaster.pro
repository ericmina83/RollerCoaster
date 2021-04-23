QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myopenglwidget.cpp \
    Camera.cpp \
    Track.cpp \
    MyShader.cpp \
    Light.cpp \
    Cube.cpp

HEADERS += \
    mainwindow.h \
    myopenglwidget.h \
    Camera.h \
    Track.h \
    MyShader.h \
    Light.h \
    Cube.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    shader.qrc \
    image.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
