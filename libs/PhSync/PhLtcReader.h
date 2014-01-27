#ifndef PHLTCREADER_H
#define PHLTCREADER_H

#include <QString>
#include <QtMultimedia/QAudioInput>
#include <QObject>
#include <QTime>



#include "ltc.h"

#include "PhTools/PhClock.h"
#include "PhTools/PhTimeCode.h"

class PhLtcReader : public QObject
{

    Q_OBJECT

public:
    explicit PhLtcReader(QObject *parent = 0);

    bool init(QString _input="");
	void close();

    static QList<QString> inputList();
    PhClock * clock();

private slots:
    void onNotify();

private:
    PhClock _clock;

    QAudioInput *_input;

    qint64 _position;
    QIODevice * _buffer;
    LTCDecoder * _decoder;
    QTime _pauseDetector;

};

#endif // PHLTCREADER_H
