#-------------------------------------------------
# Haya Trip — travel agency back office (Qt 5 / C++)
#-------------------------------------------------

QT += core gui widgets sql printsupport charts serialport network svg \
      multimedia multimediawidgets axcontainer

TARGET = HayaTrip
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14

SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    dialog_mailing.cpp \
    dialog_statistiques.cpp \
    employe.cpp \
    excel.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    qrcode.cpp \
    qrwidget.cpp \
    reservation.cpp \
    smtp.cpp \
    theme.cpp \
    voyage.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    dialog_mailing.h \
    dialog_statistiques.h \
    employe.h \
    excel.h \
    mainwindow.h \
    qcustomplot.h \
    qrcode.h \
    qrwidget.h \
    reservation.h \
    smtp.h \
    theme.h \
    voyage.h

FORMS += \
    dialog_mailing.ui \
    dialog_statistiques.ui \
    mainwindow.ui

RESOURCES += resources/resources.qrc
