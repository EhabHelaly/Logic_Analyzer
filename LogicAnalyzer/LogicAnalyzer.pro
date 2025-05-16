#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T12:22:05
#
#-------------------------------------------------

QT              += core gui widgets opengl printsupport
TARGET          = LogicAnalyzer
TEMPLATE        = app
DEFINES         += QCUSTOMPLOT_USE_OPENGL
QMAKE_CXXFLAGS  += -Wno-deprecated-copy -Wno-class-memaccess -pthread
QMAKE_LFLAGS += -pthread

SOURCES +=  main.cpp \
            mainwindow.cpp \
            qcustomplot.cpp \
            analogsignal.cpp \
            digitalsignal.cpp \
            serial.cpp

LIBS    +=  -lopengl32

HEADERS +=  mainwindow.h \
            qcustomplot.h

FORMS   +=  mainwindow.ui

RC_FILE =   LogicAnalyzer.rc
