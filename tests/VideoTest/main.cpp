#include <QtWidgets/QApplication>
#include <QFile>

#include "VideoTestWindow.h"

/**
 * @brief The application main entry point
 * @param argc Command line argument count
 * @param argv Command line argument list
 * @return 0 if the application works well.
 */
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	VideoTestSettings settings;

	VideoTestWindow w(&settings);
	w.processArg(argc, argv);
	w.show();

	return app.exec();
}
