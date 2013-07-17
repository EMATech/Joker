/**
* Copyright (C) 2012-2013 Phonations
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QObject>

#include "PhTools/PhString.h"
#include "PhStrip/PhStripDoc.h"


class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(QObject *parent = 0);
    void loadSettings();
    PhString getLastFile();
    void setLastFile(PhString fileName);
    bool openDoc(PhString fileName);
    PhStripDoc getDoc();
    bool getNaturalScrollPref();

signals:
    void docChanged();
    void onRateChanged(float rate);
    void onPositionChanged(int move);

public slots:
    //Testing
    void onRateChanged2(float rate);
    void onPositionChanged2(int move);
    //End-Testing

private:
    PhString _settingsPath;
    QSettings::Format _settingsFormat;
    QSettings * _settings;
    PhStripDoc * _doc;


};

#endif // MAINCONTROLLER_H
