#include "mainwindow.h"
#include "networkmanager.h"
#include "commentdialog.h"
#include "rescanfiledialog.h"
#include "filebrowser.h"
#include "program_exceptions.h"

#include <QMessageBox>
#include <regex>


MainWindow::MainWindow(QWidget* parent) :
	QMainWindow{parent} {
	ui.setupUi(this);

	ui.fileRadioButton->setFixedWidth(100);
	ui.urlRadioButton->setFixedWidth(100);
	ui.searchRadioButton->setFixedWidth(100);

	ui.stringFormater->setFixedSize(500, 30);
	ui.stringFormater->setPlaceholderText("No file selected");
	ui.uploadButton->setFixedHeight(30);

	ui.scanButton->setFixedSize(120, 50);
	ui.rescanButton->setFixedSize(120, 50);
	ui.commentButton->setFixedSize(120, 50);
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

	try {

		if (ui.fileRadioButton->isChecked()) {

			if (std::regex_match(input_string.toStdString(), std::regex("^(.*/)([^/]*)$"))) {

				network_manager->scanFileRequest(input_string);

			} else {
				throw InvalidFilePathException();
			}

		} else if (ui.urlRadioButton->isChecked()) {

			if (std::regex_match(input_string.toStdString(),
								 std::regex("^(ht{2}ps?:\\/{2})?(w{3}\\.)?([^:\\/\\.\\s]+)\\.([^:\\/\\.\\s]+)$"))) {
				network_manager->scanUrlRequest(input_string);

			} else {
				throw InvalidUrlNameException();
			}

		} else if (ui.searchRadioButton->isChecked()) {

			if (!std::regex_match(input_string.toStdString(), std::regex("([^:\\/\\.\\s]+)\\.([^:\\/\\.\\s]+)$"))) {

				if (!std::regex_match(input_string.toStdString(), std::regex("^(([0-9]{1,3})\\.){3}([0-9]{1,3})$"))) {
					throw InvalidIpAddressException();

				} else {
					network_manager->retrieveIpReportRequest(input_string);
				}

				throw InvalidDomainNameException();

			} else {
				network_manager->retrieveDomainReportRequest(input_string);
			}
		}

	} catch (std::exception& ex) {
		QString exception_message{ex.what()};
		QMessageBox::warning(this, "Warning", exception_message);
	}

	ui.stringFormater->clear();
}


void MainWindow::on_fileRadioButton_clicked() {
	ui.stringFormater->setPlaceholderText("No file selected");
	ui.uploadButton->setText("Choose File");
	ui.scanButton->setText("Scan it!");
	ui.stringFormater->clear();
}

void MainWindow::on_urlRadioButton_clicked() {
	ui.stringFormater->setPlaceholderText("http://example.com");
	ui.uploadButton->setText("Enter URL");
	ui.scanButton->setText("Scan it!");
	ui.stringFormater->clear();
}

void MainWindow::on_searchRadioButton_clicked() {
	ui.stringFormater->setPlaceholderText("hash, URL, domain, IP address...");
	ui.uploadButton->setText("Enter Term");
	ui.scanButton->setText("Search it!");
	ui.stringFormater->clear();
}


void MainWindow::on_uploadButton_clicked() {
	if (ui.fileRadioButton->isChecked()) {
		FileBrowser* file_browser{new FileBrowser(this)};
		file_browser->exec();

		ui.stringFormater->setText(file_browser->getFilePath());
		file_browser->setFilePath("");
	}
}


void MainWindow::on_rescanButton_clicked() {
	RescanFileDialog* rescan_file_doalog{new RescanFileDialog(this)};
	rescan_file_doalog->exec();
}


void MainWindow::on_commentButton_clicked() {
	CommentDialog* comment_dialog{new CommentDialog(this)};
	comment_dialog->exec();
}
