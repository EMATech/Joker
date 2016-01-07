#
# Copyright (C) 2012-2014 Phonations
# License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
#

HEADERS += \
    $$PWD/PhVideoEngine.h \
    $$PWD/PhVideoSettings.h
SOURCES += \
    $$PWD/PhVideoEngine.cpp

# Windows specific
win32{
	!exists($$(FFMPEG_DEV_PATH)\README.txt) {
		error("You must define a valid FFMPEG_DEV_PATH")
	}

	!exists($$(FFMPEG_SHARED_PATH)\README.txt) {
		error("You must define a valid FFMPEG_SHARED_PATH")
	}

	INCLUDEPATH += $$(FFMPEG_DEV_PATH)\include
	LIBS += -L$$(FFMPEG_DEV_PATH)\lib -lavformat -lavcodec -lavutil -lswscale -liconv


	QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_path($$(FFMPEG_SHARED_PATH)/bin/*.dll) $${RESOURCES_PATH} $${CS}
}

# Unix specific
unix {
	LIBS += -lavformat -lavcodec -lavutil -lswscale
}

# MacOS specific
mac {
	LIBS += -liconv -lbz2 -lz
}
