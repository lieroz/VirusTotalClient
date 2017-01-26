#include "mainwindow.h"
#include "networkmanager.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow{parent} {
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


void MainWindow::on_scanButton_clicked() {
	NetworkManager* network_manager{new NetworkManager};

	if (ui.fileRadioButton->isChecked()) {
		network_manager->scanFileRequest("/home/lieroz/Qt_C++_Projects/VirusTotalClient/client/test.txt");

	} else if (ui.urlRadioButton->isChecked()) {
		network_manager->scanUrlRequest("http://www.virustotal.com");

	} else if (ui.searchRadioButton->isChecked()) {
		network_manager->retrieveDomainReportRequest("ya.ru");
	}

	//	test->rescanFileRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d");
	//	test->retrieveFileScanRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d");
	//	test->retrieveUrlScanRequest("http://www.virustotal.com");
	//	test->retrieveIpReportRequest("74.125.224.72");
	//	test->makeCommentRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d", "This is a test comment");
}


void MainWindow::on_fileRadioButton_clicked() {
	ui.uploadButton->setText("Choose File");
}

void MainWindow::on_urlRadioButton_clicked() {
	ui.uploadButton->setText("Enter URL");
}

void MainWindow::on_searchRadioButton_clicked() {
	ui.uploadButton->setText("Enter Term");
}


void MainWindow::on_uploadButton_clicked() {

}
