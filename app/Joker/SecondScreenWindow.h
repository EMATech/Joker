#ifndef SECONDSCREENWINDOW_H
#define SECONDSCREENWINDOW_H

#include "PhGraphic/PhGraphicView.h"
#include "PhVideo/PhVideoEngine.h"

#include "JokerSettings.h"

class SecondScreenWindow : public PhGraphicView
{
	Q_OBJECT
public:
	explicit SecondScreenWindow(PhVideoEngine *videoEngine, PhGraphicView *shareWidget, JokerSettings *settings);

signals:

private slots:
	void onPaint(int width, int height);

private:
	PhVideoEngine *_videoEngine;
	JokerSettings *_jokerSettings;
};

#endif // SECONDSCREENWINDOW_H
