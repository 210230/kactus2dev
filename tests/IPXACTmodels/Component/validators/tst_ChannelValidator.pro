#-----------------------------------------------------------------------------
# File: tst_ChannelValidator.pro
#-----------------------------------------------------------------------------
# Project: Kactus 2
# Author: Janne Virtanen
# Date: 19.11.2015
#
# Description:
# Qt project file template for running unit tests for Enumerated Value Validator.
#-----------------------------------------------------------------------------

TEMPLATE = app

TARGET = tst_ChannelValidator

QT += core xml gui widgets testlib
CONFIG += testcase console
DEFINES += IPXACTMODELS_LIB

win32:CONFIG(release, debug|release) {
    DESTDIR = ./release
}
else:win32:CONFIG(debug, debug|release) {
    DESTDIR = ./debug
}
else:unix {
    DESTDIR = ./release
}

INCLUDEPATH += $$DESTDIR
INCLUDEPATH += ../../../../

DEPENDPATH += .
DEPENDPATH += ../../../../

OBJECTS_DIR += $$DESTDIR

MOC_DIR += ./generatedFiles
UI_DIR += ./generatedFiles
RCC_DIR += ./generatedFiles
include(tst_ChannelValidator.pri)
