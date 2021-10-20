QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    GUI/include/ \
    components/include/ \
    logic/include/ \
    photon/include/ \
    utils/include/

SOURCES += \
    GUI/src/utilsGUI.cpp \
    components/src/component.cpp \
    components/src/componentType.cpp \
    components/src/detector.cpp \
    components/src/filter.cpp \
    components/src/lensOneSided.cpp \
    components/src/lensTwoSided.cpp \
    components/src/mirrorCircle.cpp \
    components/src/mirrorElliptical.cpp \
    components/src/mirrorRectangle.cpp \
    components/src/mirrorSquare.cpp \
    \
    logic/src/exporter.cpp \
    logic/src/importer.cpp \
    logic/src/objectGenerator.cpp \
    logic/src/setupList.cpp \
    \
    photon/src/photon.cpp \
    photon/src/photonGenerator.cpp \
    \
    utils/src/bmpFileHeader.cpp \
    utils/src/bmpInfoHeader.cpp \
    utils/src/bmprgb.cpp \
    utils/src/objectPoint.cpp \
    utils/src/operators.cpp \
    utils/src/rgb.cpp \
    utils/src/utils.cpp \
    \
    GUI/src/cmpAddWindow.cpp \
    GUI/src/cmpEditWindow.cpp \
    GUI/src/cmpList.cpp \
    GUI/src/fmt_mainwindow.cpp \
    GUI/src/prjNewWindow.cpp \
    GUI/src/saveStpAsWindow.cpp \
    GUI/src/simStartWindow.cpp \
    fmt_simulator.cpp

HEADERS += \
    GUI/include/utilsGUI.hpp \
    components/include/component.hpp \
    components/include/componentType.hpp \
    components/include/detector.hpp \
    components/include/filter.hpp \
    components/include/lensOneSided.hpp \
    components/include/lensTwoSided.hpp \
    components/include/mirrorCircle.hpp \
    components/include/mirrorElliptical.hpp \
    components/include/mirrorRectangle.hpp \
    components/include/mirrorSquare.hpp \
    \
    logic/include/config.hpp \
    logic/include/exporter.hpp \
    logic/include/importer.hpp \
    logic/include/objectGenerator.hpp \
    logic/include/setupList.hpp \
    \
    photon/include/photon.hpp \
    photon/include/photonGenerator.hpp \
    \
    utils/include/bmpFileHeader.hpp \
    utils/include/bmpInfoHeader.hpp \
    utils/include/bmprgb.hpp \
    utils/include/objectPoint.hpp \
    utils/include/operators.hpp \
    utils/include/rgb.hpp \
    utils/include/utils.hpp \
    \
    GUI/include/cmpAddWindow.hpp \
    GUI/include/cmpEditWindow.hpp \
    GUI/include/cmpList.hpp \
    GUI/include/fmt_mainwindow.hpp \
    GUI/include/prjNewWindow.hpp \
    GUI/include/saveStpAsWindow.hpp \
    GUI/include/simStartWindow.hpp

FORMS += \
    GUI/include/fmt_mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
