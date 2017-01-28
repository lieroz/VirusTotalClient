#include "rescanfiledialog.h"
#include "networkmanager.h"


RescanFileDialog::RescanFileDialog(QWidget* parent) :
	QDialog(parent) {
	ui.setupUi(this);

	ui.lineEdit->setPlaceholderText("Enter file sha256...");
}


void RescanFileDialog::changeEvent(QEvent* e) {
	QDialog::changeEvent(e);

	switch (e->type()) {

		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			break;

		default:
			break;
	}
}


void RescanFileDialog::on_submitButton_clicked() {
	NetworkManager* network_manager{new NetworkManager};
	network_manager->rescanFileRequest(ui.lineEdit->text());
	this->close();
}
