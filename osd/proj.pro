#-------------------------------------------------
#
# Project created by QtCreator 2013-01-09T11:51:51
#
#-------------------------------------------------

QT  += core gui xml  


CONFIG += c++11				
CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osd
TEMPLATE = app


SOURCES += main.cpp\
configmgr.cpp \
mainwindow.cpp \
OsdImage.cpp \
OsdProjMode.cpp \
QboxNet.cpp \
msgBase.cpp \
TestQbox.cpp \
Screen.cpp \
deviceswnd.cpp\
wallwnd.cpp\
wndwnd.cpp \
chnwnd.cpp \
ringwnd.cpp \
ring.cpp \
wnd.cpp \
mode.cpp\
task.cpp\
modewnd.cpp \
taskwnd.cpp \

HEADERS  +=  \
configmgr.h \
mainwindow.h \
OsdImage.h \
OsdProjMode.h \
QboxNet.h \
msgBase.h \
TestQbox.h \
Screen.h \
deviceswnd.h\
wallwnd.h\
wndwnd.h \
chnwnd.h \
ringwnd.h \
ring.h \
wnd.h \
mode.h\
task.h\
modewnd.h \
taskwnd.h \

FORMS    += \
mainwindow.ui \
OsdImage.ui \
OsdProjMode.ui \
deviceswnd.ui \
TestQbox.ui \
wallwnd.ui \
wndwnd.ui \
chnwnd.ui \
ringwnd.ui \
modewnd.ui \
taskwnd.ui \


LIBS += -lws2_32
DEFINES +=	_WIN32_WINNT=0x0501 \
_CRT_SECURE_NO_DEPRECATE \
BOOST_DATE_TIME_NO_LIB BOOST_REGEX_NO_LIB BOOST_ALL_NO_LIB=1


INCLUDEPATH += $$PWD/inc
INCLUDEPATH += $$PWD/../3rdParty/inc
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
