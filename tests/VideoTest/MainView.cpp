#include "MainView.h"
#include "ui_MainView.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QFileInfo>
#include <QFileDialog>

MainView::MainView()
	: QMainWindow(0),
	  ui(new Ui::MainView)
{

	ui->setupUi(this);
	_clock = ui->_videoView->getClock();
	ui->mediaController->setClock(_clock);

	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpenFile()));
	connect(&timer, SIGNAL(timeout()), ui->_videoView, SLOT(checkVideoPosition()));

	timer.start(10);
}


MainView::~MainView()
{
	delete ui;
}

bool MainView::openFile(QString fileName)
{
    QFileInfo fileInfo(fileName);
    if (fileInfo.exists())
    {
		ui->_videoView->open(fileName);
#warning TODO read media length from video file
		ui->mediaController->setMediaLength(7500);
#warning TODO read first frame from video file
		ui->mediaController->setFirstFrame(0);

		_clock->setRate(0.0);
		return true;
    }
	return false;
}


void MainView::onOpenFile()
{
	 QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());
	 openFile(fileName); // TODO: show error in case of error
}



void MainView::on_actionPlay_pause_triggered()
{
	if(_clock->rate()!=0)
		_clock->setRate(0);
	else
		_clock->setRate(1);
}

void MainView::on_actionNext_frame_triggered()
{
    _clock->setFrame(_clock->frame() + 1);
}

void MainView::on_actionPrevious_frame_triggered()
{
	_clock->setFrame(_clock->frame() - 1);
}
