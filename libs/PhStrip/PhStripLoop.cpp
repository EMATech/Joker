/**
 * @file
 * @copyright (C) 2012-2014 Phonations
 * @license http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 */


#include "PhStripLoop.h"

PhStripLoop::PhStripLoop()
{
	_number = 0;
}

PhStripLoop::PhStripLoop(int number, PhTime TimeIn) : PhStripObject(TimeIn)
{
	_number = number;
}
