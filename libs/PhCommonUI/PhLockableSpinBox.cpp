#include <QEvent>

#include "PhTools/PhDebug.h"
#include "PhLockableSpinBox.h"

PhLockableSpinBox::PhLockableSpinBox(QWidget *parent) :
	QSpinBox(parent), _pressCounter(0)
{
	setEnabled(false);
	this->installEventFilter(this);
}

bool PhLockableSpinBox::eventFilter(QObject *sender, QEvent *event)
{
	Q_UNUSED(sender);
	switch(event->type()) {
	case QEvent::MouseButtonPress:
		if(_pressTimer.elapsed() > 250)
			_pressCounter = 0;
		PHDEBUG << _pressCounter++;
		_pressTimer.restart();
		if(_pressCounter > 7) {
			PHDEBUG << "switch";
			this->setEnabled(true);
			_pressCounter = 0;
		}
		break;
	default:
		break;
	}

	return false;
}
