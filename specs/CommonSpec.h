/**
 * Copyright (C) 2012-2014 Phonations
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 */

#ifndef COMMONSPEC_H
#define COMMONSPEC_H

#include <QImage>

#include "PhSync/PhTimeCode.h"


std::string f2s(PhFrame frame, PhTimeCodeType tcType);

std::string t2s(PhTime time, PhTimeCodeType tcType);

PhTime s2t(QString string, PhTimeCodeType tcType);

std::string t2s25(PhTime time);

PhTime s2t25(QString string);

bool compareImage(QImage result, QImage expected, QString testName, int gap = 0);

#endif // COMMONSPEC_H
