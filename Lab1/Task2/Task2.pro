QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Circle.cpp \
    Figure.cpp \
    Rectangle.cpp \
    Rhombus.cpp \
    Square.cpp \
    Triangle.cpp \
    circledialog.cpp \
    main.cpp \
    mainwindow.cpp \
    rectangledialog.cpp \
    rhombusdialog.cpp \
    squaredialog.cpp \
    triangledialog.cpp

HEADERS += \
    Circle.h \
    Figure.h \
    Rectangle.h \
    Rhombus.h \
    Square.h \
    Triangle.h \
    circledialog.h \
    mainwindow.h \
    rectangledialog.h \
    rhombusdialog.h \
    squaredialog.h \
    triangledialog.h

FORMS += \
    circledialog.ui \
    mainwindow.ui \
    rectangledialog.ui \
    rhombusdialog.ui \
    squaredialog.ui \
    triangledialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
