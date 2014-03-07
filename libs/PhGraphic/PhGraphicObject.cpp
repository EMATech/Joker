/**
 * @file
 * @copyright (C) 2012-2014 Phonations
 * @license http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 */

#include "PhGraphicObject.h"

PhGraphicObject::PhGraphicObject(int x, int y) : _x(x), _y(y), _z(0), _color(Qt::white)
{
}

PhGraphicObject::~PhGraphicObject()
{
}

void PhGraphicObject::dispose()
{
}

bool PhGraphicObject::init()
{
	return true;
}

void PhGraphicObject::setPosition(int x, int y, int z)
{
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}


void PhGraphicObject::setX(int x) {
	_x = x;
}

void PhGraphicObject::setY(int y) {
	_y = y;
}

void PhGraphicObject::setZ(int z)
{
	_z = z;
}


int PhGraphicObject::getX() {
	return _x;
}

int PhGraphicObject::getY() {
	return _y;
}

int PhGraphicObject::getZ()
{
	return _z;
}


QColor PhGraphicObject::getColor() {
	return _color;
}

void PhGraphicObject::setColor(QColor color) {
	_color = color;
}

