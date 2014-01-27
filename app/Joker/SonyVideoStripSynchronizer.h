#ifndef SONYVIDEOSTRIPSYNCHRONIZER_H
#define SONYVIDEOSTRIPSYNCHRONIZER_H

#include <QObject>

#include "PhTools/PhClock.h"

class VideoStripSynchronizer : public QObject
{
	Q_OBJECT
public:
	VideoStripSynchronizer();

	void setStripClock(PhClock *clock);
	PhClock * stripClock() { return _stripClock; }
	void setVideoClock(PhClock *clock);
	PhClock * videoClock() { return _videoClock; }
    void setSyncClock(PhClock *clock);
    PhClock * syncClock() { return _syncClock; }

private slots:
	void onStripFrameChanged(PhFrame frame, PhTimeCodeType tcType);
	void onStripRateChanged(PhRate rate);
	void onVideoFrameChanged(PhFrame frame, PhTimeCodeType tcType);
	void onVideoRateChanged(PhRate rate);
	void onVideoTCTypeChanged(PhTimeCodeType tcType);
	void onSonyFrameChanged(PhFrame frame, PhTimeCodeType tcType);
	void onSonyRateChanged(PhRate rate);
private:
	PhClock * _stripClock;
	PhClock * _videoClock;
    PhClock * _syncClock;
	bool _settingStripFrame;
	bool _settingVideoFrame;
	bool _settingSonyFrame;
	bool _settingStripRate;
	bool _settingVideoRate;
	bool _settingSonyRate;
};

#endif // SONYVIDEOSTRIPSYNCHRONIZER_H
