#-------------------------------------------------
#
# Project created by QtCreator 2013-01-09T11:51:51
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ac1608
TEMPLATE = app


SOURCES += main.cpp\
homepage.cpp \
configmgr.cpp \
peqwnd.cpp \
    snmpnet.cpp \
    mainwindow.cpp \
    presetwnd.cpp \
    copyparamwnd.cpp \
    changepasswordwnd.cpp \
    inputgainctrlwnd.cpp \
    highpasswnd.cpp \
    gatenomwnd.cpp \
    meterswnd.cpp \
    matrixmixerwnd.cpp \
    level8chwnd.cpp \
    deviceswnd.cpp

HEADERS  +=  snmpnet.h \
homepage.h \
peqwnd.h \
    configmgr.h \
	mainwindow.h \
    presetwnd.h \
    copyparamwnd.h \
    changepasswordwnd.h \
    inputgainctrlwnd.h \
    highpasswnd.h \
    gatenomwnd.h \
    meterswnd.h \
    matrixmixerwnd.h \
    level8chwnd.h \
    deviceswnd.h

FORMS    += mainwindow.ui \
homepage.ui \
peqwnd.ui \
    presetwnd.ui \
    copyparamwnd.ui \
    changepasswordwnd.ui \
    inputgainctrlwnd.ui \
    highpasswnd.ui \
    gatenomwnd.ui \
    level8chwnd.ui \
    deviceswnd.ui \
    meterswnd.ui \
    matrixmixerwnd.ui


LIBS += -lws2_32

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lnetsnmp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lnetsnmpd
else:unix: LIBS += -L$$PWD/lib/ -lnetsnmp



INCLUDEPATH += $$PWD/inc
DEPENDPATH += $$PWD/inc
