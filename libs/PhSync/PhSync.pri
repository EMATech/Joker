#
# Copyright (C) 2012-2014 Phonations
# License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
#

QT += serialport

HEADERS += \
    ../../libs/PhSync/PhSonyController.h \
    ../../libs/PhSync/PhSonyMasterController.h \
    ../../libs/PhSync/PhSonySlaveController.h \
    ../../libs/PhSync/tests/PhSonyControllerTest.h \
    ../../libs/PhSync/PhSyncSettings.h


SOURCES += \
    ../../libs/PhSync/PhSonyController.cpp \
    ../../libs/PhSync/PhSonyMasterController.cpp \
    ../../libs/PhSync/PhSonySlaveController.cpp \
    ../../libs/PhSync/tests/PhSonyControllerTest.cpp \

ltc {
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lltc

HEADERS += \
	../../libs/PhSync/PhLtcReader.h \
    ../../libs/PhSync/PhLtcWriter.h

SOURCES += \
	../../libs/PhSync/PhLtcReader.cpp \
    ../../libs/PhSync/PhLtcWriter.cpp

DEFINES += USE_LTC
}

