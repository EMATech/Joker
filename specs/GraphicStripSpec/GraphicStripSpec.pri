#-------------------------------------------------
#
# Project created by QtCreator 2014-09-01T17:54:58
#
#-------------------------------------------------

include($$TOP_ROOT/libs/PhStrip/PhStrip.pri)
include($$TOP_ROOT/libs/PhGraphicStrip/PhGraphicStrip.pri)

HEADERS += $$TOP_ROOT/specs/GraphicStripSpec/GraphicStripSpecSettings.h
SOURCES += $$TOP_ROOT/specs/GraphicStripSpec/GraphicStripSpec.cpp

QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_path($${TOP_ROOT}/data/img/*.bmp) . $${CS}
QMAKE_POST_LINK += $${QMAKE_COPY} $$shell_path($${TOP_ROOT}/data/fonts/*) . $${CS}
