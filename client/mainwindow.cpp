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
//	test->scanFileRequest("/home/lieroz/Qt_C++_Projects/VirusTotalClient/client/test.txt");
//	test->scanUrlRequest("http://www.virustotal.com");
//	test->rescanFileRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d");
//	test->retrieveFileScanRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d");
//	test->retrieveUrlScanRequest("http://www.virustotal.com");
//	test->retrieveIpReportRequest("74.125.224.72");
//	test->retrieveDomainReportRequest("ya.ru");
	test->makeCommentRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d", "This is a test comment");
}
