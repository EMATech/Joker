/**
 * @file
 * @copyright (C) 2012-2014 Phonations
 * @license http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 */

#ifndef PHTIME_H
#define PHTIME_H

#include <QtGlobal>
#include <limits>

/** @brief PhTime is a type used for time value */
typedef qint64 PhTime;

/** @brief PhTimeScale is a type used for time scale value */
typedef int PhTimeScale;

/** @brief PhRate is a type used for rate value */
typedef double PhRate;

/** @brief Type for the timecode frame */
typedef long PhFrame;

/** @brief The maximum PhFrame value */
#define PHFRAMEMAX std::numeric_limits<PhFrame>::max()

/** @brief The minimum PhFrame value */
#define PHFRAMEMIN std::numeric_limits<PhFrame>::min()

#endif // PHTIME_H
