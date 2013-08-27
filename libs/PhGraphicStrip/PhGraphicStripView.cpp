/**
* Copyright (C) 2012-2013 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include "PhGraphicStripView.h"

PhGraphicStripView::PhGraphicStripView(QWidget *parent)
	: PhGraphicView( parent ), _doc(this), _currentFont(NULL), _trackNumber(4)
{
	// update the view content when the doc changes :
	this->connect(&_doc, SIGNAL(changed()), this, SLOT(updateView()));

    // This is used to make some time-based test
	_test = new QTime();
	_test->start();
}

PhStripDoc *PhGraphicStripView::doc()
{
	return &_doc;
}

PhClock *PhGraphicStripView::clock()
{
	return &_clock;
}

bool PhGraphicStripView::init()
{
	qDebug() << "PhGraphicStripView::init()";

	// Load font
	if(!setCurrentFont("Bedizen.ttf"))
		return false;

	//This clear the data stored
	clearData();

    //Load the strip background
	_stripBackgroundImage = new PhGraphicImage("motif-240.png");
	_stripBackgroundImage->init();

	updateView();

	return true;
}

void PhGraphicStripView::clearData()
{
	foreach(PhGraphicRect * gCut, _graphicCuts.values())
	{
		delete gCut;
	}
	foreach(PhGraphicText * gText, _graphicTexts.values())
	{
		delete gText;
	}
	_graphicCuts.clear();
	_graphicTexts.clear();
}


bool PhGraphicStripView::setCurrentFont(QString fontFile)
{
	qDebug() << "setCurrentFont : " << fontFile;

	if(!QFile::exists(fontFile))
	{
		qDebug() << "File does'nt exists : " << fontFile;
		return false;
	}
	_currentFont = new PhFont(fontFile, 150);

	if(!_currentFont->init())
		return false;

	return true;
}

void PhGraphicStripView::updateView()
{
	qDebug() << "updateView";
	if(!_currentFont)
	{
		qDebug() << "updateView not ready";
		return;
	}

	clearData();

	// Load the peoples
	foreach(PhPeople * people, _doc.getPeoples())
	{
		PhGraphicText * gPeople = new PhGraphicText(_currentFont, people->getName());
		gPeople->setColor(new QColor(people->getColor()));
		gPeople->setWidth(people->getName().length() * 4);
		gPeople->setHeight(0.5f);
		gPeople->setFont(_currentFont);

		gPeople->init();

		_graphicPeoples[people] = gPeople;
	}

	//Load the texts
	foreach(PhStripText * text, _doc.getTexts())
	{
		PhGraphicText * gText = new PhGraphicText( _currentFont, text->getContent());
		float track = text->getTrack();

		gText->setX(text->getTimeIn());
		gText->setY(track);
		gText->setZ(-1);
		gText->setWidth(text->getTimeOut() - text->getTimeIn());
		gText->setHeight(1.0f);
		if(text->getPeople())
			gText->setColor(new QColor(text->getPeople()->getColor()));
		gText->setFont(_currentFont);

		gText->init();

		_graphicTexts[text] = gText;
	}

	//Load the cuts
	foreach(PhStripCut * cut, _doc.getCuts())
	{
		PhGraphicSolidRect *gCut = new PhGraphicSolidRect();
		gCut->setColor(new QColor(0, 0, 0));
		gCut->setX(cut->getTimeIn());
		gCut->setWidth(0.5f);
		gCut->setHeight(_trackNumber);
		gCut->setZ(-2);

		_graphicCuts[cut] = gCut;
	}

	qDebug() << "updateView ok";
}

void PhGraphicStripView::paint()
{
	_clock.tick(60);

	float pixelPerFrame = 8;
	float length = this->width() / pixelPerFrame;
	float fps = PhTimeCode::getFps(_clock.getTCType());
	float t = _clock.time() * fps / _clock.timeScale();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(t, t + length, _trackNumber, 0, 0, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

//	qDebug() << "PhGraphicStripView::paint()";

	//Set the background color to red
	glClearColor(1,0,0,1);

	//Time-based test
//	qDebug() << _test->elapsed(); //<< " : " << _xmove;

//    //Draw backgroung picture
	float aspectRatio = 1.2f * this->width() / this->height();
	_stripBackgroundImage->setTextureCoordinate(aspectRatio, 1);
	_stripBackgroundImage->setX(floorf(t / aspectRatio) * aspectRatio);
	_stripBackgroundImage->setSize(length + aspectRatio, _trackNumber);
	_stripBackgroundImage->draw();

	int minSpaceBetweenPeople = 50;
	int spaceBetweenPeopleAndText = 4;
	PhStripText ** lastTextList = new PhStripText*[_trackNumber];
	for(int i = 0; i < _trackNumber; i++)
		lastTextList[i] = NULL;

	foreach(PhStripText * text, _doc.getTexts())
	{
		PhGraphicText* gText = _graphicTexts[text];

		int track = text->getTrack();

		gText->draw();

		PhStripText * lastText = lastTextList[track];
		// Display the people name only if one of the following condition is true:
		// - it is the first text
		// - it is a different people
		// - the distance between the latest text and the current is superior to a limit
		if((lastText == NULL) || (lastText->getPeople() != text->getPeople()) || (text->getTimeIn() - lastText->getTimeOut() > minSpaceBetweenPeople))
		{
			PhGraphicText * gPeople = _graphicPeoples[text->getPeople()];
			gPeople->setX(text->getTimeIn() - gPeople->getWidth() - spaceBetweenPeopleAndText);
			gPeople->setY(track);

			gPeople->draw();
		}

		lastTextList[track] = text;
	}

	foreach(PhStripCut * cut, _doc.getCuts())
		_graphicCuts[cut]->draw();
}
