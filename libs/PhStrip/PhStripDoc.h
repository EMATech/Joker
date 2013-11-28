#ifndef PHSTRIPDOC_H
#define PHSTRIPDOC_H

#include <QList>
#include <QMap>
#include <QtXml>
#include <QXmlStreamWriter>
#include <QDomDocument>

#include "PhTools/PhTimeCode.h"

#include "PhPeople.h"
#include "PhStripCut.h"
#include "PhStripLoop.h"
#include "PhStripObject.h"
#include "PhStripText.h"
#include "PhStripOff.h"

class PhStripDoc : public QObject
{
	Q_OBJECT

public:
     /**
     * @brief PhStripDoc
     * @param filename
     * Constructor
     */
    explicit PhStripDoc(QObject *parent = 0);

    QList<PhStripCut *> getCuts();

    /**
     * @brief getTitle
     * @return _title
     */
	QString getTitle();
    /**
     * @brief getVideoTimestamp
     * @return _videoTimestamp
     */
    PhTime getVideoTimestamp();

	/**
	 * @brief getFilePath
	 * @return _filePath
	 */
	QString getFilePath();

    /**
     * @brief getVideoPath
     * @return _videoPath
     */
	QString getVideoPath();

	QString getAuthorName() { return _authorName;}

    /**
     * @brief getLastPosition
     * @return _lastPosition
     */
    PhFrame getLastFrame();

    /**
     * @brief getTimeScale
     * @return
     */
    int getTimeScale();

    PhTimeCodeType getTCType();

	/**
     * @brief getActors
     * @return _actors
     */
	QMap<QString, PhPeople *> getPeoples();
    /**
     * @brief getTexts
     * @return _texts
     */
    QList<PhStripText *> getTexts();

	/**
	 * @brief getLoops
	 * @return _loops
	 */
	QList<PhStripLoop *> getLoops();

	/**
	 * @brief getOffs
	 * @return _offs
	 */
	QList<PhStripOff *> getOffs();

    /**
     * @brief setTitle
     * @param _title
     */
	void setTitle(QString _title);
    /**
     * @brief setVideoTimestamp
     * @param videoTimestamp
     */
    void setVideoTimestamp(PhTimeCode videoTimestamp);
    /**
     * @brief setVideoPath
     * @param videoPath
     */
	void setVideoPath(QString videoPath);
    /**
     * @brief setTimeScale
     * @param timeScale
     */
    void setTimeScale(int timeScale);
    /**
     * @brief openDetX
     * @param filename
     * @return
     */
	bool importDetX(QString filename);
	bool openStripFile(QString fileName);
	bool saveStrip(QString fileName, QString lastTC);

	// First version : Create StripDoc for testing purposes
	bool createDoc(QString text, int nbPeople, int nbLoop, int nbText, int nbTrack, PhTime videoTimeCode);

    int getNbTexts();

	PhFrame getPreviousTextFrame(PhFrame frame);

	PhFrame getPreviousLoopFrame(PhFrame frame);

	PhFrame getPreviousCutFrame(PhFrame frame);

	PhFrame getPreviousElementFrame(PhFrame frame);

	PhFrame getNextTextFrame(PhFrame frame);

	PhFrame getNextLoopFrame(PhFrame frame);

	PhFrame getNextCutFrame(PhFrame frame);

	PhFrame getNextElementFrame(PhFrame frame);

	PhFrame getFrameIn();

	PhFrame getFrameOut();
signals:
	void changed();

private:
    void reset();
    /**
     * Title of the corresponding audiovisual content.
     */
	QString _title;
    /**
     * Starting time of the video content refered by the videoPath : String
     */
    PhTime _videoFrameStamp;
    /**
     * @brief _lastPosition
     */
    PhTime _lastFrame;

	/**
	 * Path to the file content.
	 */
	QString _filePath;

    /**
     * Path to the video content.
     */
	QString _videoPath;
    /**
     * Amount of time units per second.
     */
    int _timeScale;

	PhTimeCodeType _tcType;

	QString _authorName;

    /**
     * List of PhPeople from the file
     */
	QMap<QString, PhPeople *> _peoples;

    /**
     * List of PhStripText from the file
     */
    QList<PhStripText *> _texts;

    /**
     * List of PhStripCut form the file
     */
     QList<PhStripCut *> _cuts;

     /**
      * List of PhStripLoop from the file
      */
     QList<PhStripLoop *> _loops;

	 /**
	  * List of PhStripOff from the file
	  */
	 QList<PhStripOff *> _offs;

     int _nbTexts;
	 void addText(PhPeople * actor, PhTime start, PhTime end, QString sentence,int track, int ite);
};

#endif // PHSTRIPDOC_H
