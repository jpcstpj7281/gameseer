#-------------------------------------------------
#
# Project created by QtCreator 2013-01-09T11:51:51
#
#-------------------------------------------------

QT  += core gui xml  

#greaterThan(QT_MAJOR_VERSION, 4) {
#    QT += widgets quick
#} else {
    QT += declarative
#}

QMAKE_CXXFLAGS += -std=gnu++0x  #Qt4
CONFIG += c++11					#Qt5

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osd
TEMPLATE = app


SOURCES += main.cpp\
configmgr.cpp \
snmpnetwnd.cpp \
snmpnet.cpp \
mainwindow.cpp \
deviceswnd.cpp

HEADERS  +=  snmpnet.h \
snmpnetwnd.h \
configmgr.h \
mainwindow.h \
deviceswnd.h

FORMS    += \
mainwindow.ui \
snmpnetwnd.ui \
deviceswnd.ui \


LIBS += -lws2_32

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lnetsnmp -lAdvapi32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lnetsnmpd -lAdvapi32
else:unix: LIBS += -L$$PWD/lib/ -lnetsnmp



INCLUDEPATH += $$PWD/inc
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD/inc



Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
