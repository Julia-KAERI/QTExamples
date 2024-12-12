QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DESTDIR = $(PWD)
message(The project will be installed in the value of $(PWD))
message(when the Makefile is processed.)

#INCLUDEPATH += ${VCPKG}
INCLUDEPATH += /Users/jiyong/vcpkg/packages/eigen3_x64-osx/include
INCLUDEPATH += /Users/jiyongso/Lib/vcpkg/packages/eigen3_arm64-osx/include


SOURCES += \
    main.cpp \
    plotter.cpp \
    qcustomplot.cpp

HEADERS += \
    plotter.hpp \
    qcustomplot.hpp

FORMS += \
    plotter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
