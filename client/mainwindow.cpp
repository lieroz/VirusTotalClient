#include "mainwindow.h"
#include "networkmanager.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent) {
	ui.setupUi(this);
}

void MainWindow::changeEvent(QEvent* e) {
	QMainWindow::changeEvent(e);

	switch (e->type()) {
		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			break;

		default:
			break;
	}
}

void MainWindow::on_pushButton_clicked() {
	NetworkManager* test = new NetworkManager;
	test->processRequest();
}