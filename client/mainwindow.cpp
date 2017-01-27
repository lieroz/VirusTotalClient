#include "mainwindow.h"
#include "networkmanager.h"
#include "filebrowser.h"

#include <QFileDialog>
#include <regex>


MainWindow::MainWindow(QWidget* parent) :
	QMainWindow{parent} {
	ui.setupUi(this);

	ui.fileRadioButton->setFixedWidth(100);
	ui.urlRadioButton->setFixedWidth(100);
	ui.searchRadioButton->setFixedWidth(100);

	ui.stringFormater->setFixedSize(500, 30);
	ui.uploadButton->setFixedHeight(30);

	ui.scanButton->setFixedSize(100, 50);
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
	QString input_string = ui.stringFormater->text();

	if (ui.fileRadioButton->isChecked()) {

		if (std::regex_match(input_string.toStdString(), std::regex("^(.*/)([^/]*)$"))) {
			network_manager->scanFileRequest(input_string);

		} else {
			qDebug() << "DOESN'T MATCH!!!";
		}

	} else if (ui.urlRadioButton->isChecked()) {

		if (std::regex_match(input_string.toStdString(),
							 std::regex("^(ht{2}ps?:\\/{2})?(w{3}\\.)?([^:\\/\\.\\s]+)\\.([^:\\/\\.\\s]+)$"))) {
			network_manager->scanUrlRequest(input_string);

		} else {
			qDebug() << "DOESN'T MATCH!!!";
		}

	} else if (ui.searchRadioButton->isChecked()) {

		if (std::regex_match(input_string.toStdString(), std::regex("([^:\\/\\.\\s]+)\\.([^:\\/\\.\\s]+)$"))) {
			network_manager->retrieveDomainReportRequest(input_string);

		} else if (std::regex_match(input_string.toStdString(), std::regex("^(([0-9]{1,3})\\.){3}([0-9]{1,3})$"))) {
			network_manager->retrieveIpReportRequest(input_string);

		} else {
			qDebug() << "DOESN'T MATCH!!!";
		}
	}

	ui.stringFormater->clear();

	//	test->rescanFileRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d");
	//	test->retrieveFileScanRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d");
	//	test->retrieveUrlScanRequest("http://www.virustotal.com");
	//	test->makeCommentRequest("0f272f560805b42285bb0cd73f8048453be9d0dfdee8b6d573619881dd29a18d", "This is a test comment");
}


void MainWindow::on_fileRadioButton_clicked() {
	ui.uploadButton->setText("Choose File");
	ui.stringFormater->clear();
	ui.rescanButton->setVisible(true);
}

void MainWindow::on_urlRadioButton_clicked() {
	ui.uploadButton->setText("Enter URL");
	ui.stringFormater->clear();
	ui.rescanButton->setVisible(false);
}

void MainWindow::on_searchRadioButton_clicked() {
	ui.uploadButton->setText("Enter Term");
	ui.stringFormater->clear();
	ui.rescanButton->setVisible(false);
}


void MainWindow::on_uploadButton_clicked() {
	if (ui.fileRadioButton->isChecked()) {
		FileBrowser* file_browser{new FileBrowser(this)};
		file_browser->exec();

		ui.stringFormater->setText(file_browser->getFilePath());
		file_browser->setFilePath("");
	}
}
