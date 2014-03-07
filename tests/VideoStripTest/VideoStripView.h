#ifndef VIDEOSTRIPVIEW_H
#define VIDEOSTRIPVIEW_H

#include "PhGraphic/PhGraphicView.h"
#include "PhVideo/PhVideoEngine.h"
#include "PhGraphicStrip/PhGraphicStrip.h"

class VideoStripView : public PhGraphicView
{
	Q_OBJECT
public:
	explicit VideoStripView(QWidget *parent = 0);

	PhVideoEngine * videoEngine() {
		return &_videoEngine;
	}
	PhGraphicStrip * strip() {
		return &_strip;
	}
protected:
	bool init();
	void paint();

private:
	PhVideoEngine _videoEngine;
	PhGraphicStrip _strip;
};

#endif // VIDEOSTRIPVIEW_H
