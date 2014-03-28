/**
 * Copyright (C) 2012-2014 Phonations
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 */

#ifndef PHAVDECODER_H
#define PHAVDECODER_H

extern "C" {
#ifndef INT64_C
/** see http://code.google.com/p/ffmpegsource/issues/detail?id=11#c13 */
#define INT64_C(c) (c ## LL)
/** and http://code.google.com/p/ffmpegsource/issues/detail?id=11#c23 */
#define UINT64_C(c) (c ## ULL)
#endif

#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}


#include <QObject>
#include <QMap>
#include <QSemaphore>
#include <QMutex>

#include "PhGraphic/PhGraphicTexturedRect.h"
#include "PhTools/PhTime.h"
#include "PhTools/PhTimeCode.h"

class PhAVDecoder : public QObject
{
	Q_OBJECT
public:
	explicit PhAVDecoder(int bufferSize, QObject *parent = 0);
	~PhAVDecoder();

	bool open(QString fileName);
	void close();

	PhTimeCodeType timeCodeType();
	PhFrame firstFrame();
	/**
	 * @brief Set first frame
	 * @param frame the new first frame
	 */
	void setFirstFrame(PhFrame frame);

	int width();
	int height();
	/**
	 * @brief Get the length
	 * @return the length of the video
	 */
	PhFrame length();
	/**
	 * @brief get frame per second
	 * @return the FPS of the video file
	 */
	float framePerSecond();
	/**
	 * @brief Get the codec name
	 * @return the codec name
	 */
	QString codecName();

	void setDeintrelace(bool deintrelace);

	int bufferOccupation();

	uint8_t* getBuffer(PhFrame frame);
signals:
	void finished();
	void error(QString err);

public slots:
	void process();

	void onFrameChanged(PhFrame frame, PhTimeCodeType tcType);
	void onRateChanged(PhRate rate);

private:
	int64_t frame2time(PhFrame f);
	PhFrame time2frame(int64_t t);

	int _bufferSize;
	QSemaphore _framesFree;
	QMap<PhFrame, uint8_t * > _bufferMap;
	QMutex _bufferMutex;
	void clearBuffer();

	PhFrame _firstFrame;
	PhFrame _currentFrame;
	int _direction;

	AVFormatContext * _pFormatContext;
	AVStream *_videoStream;
	AVFrame * _videoFrame;
	struct SwsContext * _pSwsCtx;
	bool _videoDeintrelace;

	AVStream *_audioStream;
	AVFrame * _audioFrame;

	bool _interupted;
};

#endif // PHAVDECODER_H
