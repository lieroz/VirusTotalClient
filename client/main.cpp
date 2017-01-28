#include "mainwindow.h"
#include "overlaywidget.h"

#include <QApplication>
#include <QDesktopWidget>


int main(int argc, char* argv[]) {
	QApplication application{argc, argv};

	MainWindow main_window{};
	main_window.move(QApplication::desktop()->screen()->rect().center() - main_window.rect().center());
	OverlayWidget overlay(&main_window);
	main_window.show();

	return application.exec();
}
