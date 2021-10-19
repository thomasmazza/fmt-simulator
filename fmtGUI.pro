QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    GUI/include/

SOURCES += \
    GUI/src/cmpAddWindow.cpp \
    GUI/src/cmpEditWindow.cpp \
    GUI/src/cmpList.cpp \
    GUI/src/fmt_mainwindow.cpp \
    GUI/src/prjNewWindow.cpp \
    GUI/src/saveStpAsWindow.cpp \
    GUI/src/simStartWindow.cpp \
    GUI/src/utils.cpp \
    fmt_simulator.cpp

HEADERS += \
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
