#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <PhGraphicStrip/PhGraphicStripView.h>
#include <PhVideo/PhVideoView.h>
#include <QMessageBox>
#include "PhSync/PhStripVideoSynchronizer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void openFile(QString fileName);

	PhGraphicStripView * getStripView(){return _stripView;};

	bool openVideoFile(QString videoFileName);

private slots:
	void onOpenFile();
	void onFrameChanged(PhFrame frame, PhTimeCodeType tcType);
	void onRateChanged(PhRate rate);

	void on_actionPlay_pause_triggered();

	void on_actionPlay_backward_triggered();

	void on_actionStep_forward_triggered();

	void on_actionStep_backward_triggered();

	void on_actionStep_time_forward_triggered();

	void on_actionStep_time_backward_triggered();

	void on_action_3_triggered();

	void on_action_1_triggered();

	void on_action_0_5_triggered();

	void on_action0_triggered();

	void on_action0_5_triggered();

	void on_action1_triggered();

	void on_action3_triggered();

	void on_actionGo_To_triggered();

	void on_actionOpen_Video_triggered();

	void on_actionSet_Time_Code_triggered();

private:
	Ui::MainWindow *ui;
	PhGraphicStripView *_stripView;
	PhStripDoc *_doc;
	PhClock *_stripClock;
	PhStripVideoSynchronizer _stripVideoSynchronizer;

};

#endif // MAINWINDOW_H