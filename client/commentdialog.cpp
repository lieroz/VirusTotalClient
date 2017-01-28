#include "commentdialog.h"
#include "networkmanager.h"


CommentDialog::CommentDialog(QWidget* parent) :
	QDialog(parent) {
	ui.setupUi(this);

	this->setWindowTitle("CommentDialog");
	ui.lineEdit->setPlaceholderText("Enter file/url/domain/ip sha256...");
	ui.textEdit->setPlaceholderText("Enter comment message here...");
}


void CommentDialog::changeEvent(QEvent* e) {
	QDialog::changeEvent(e);

	switch (e->type()) {

		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			break;

		default:
			break;
	}
}


void CommentDialog::on_submitButton_clicked() {
	NetworkManager* network_manager{new NetworkManager};
	network_manager->makeCommentRequest(ui.lineEdit->text(), ui.textEdit->toPlainText());
	this->close();
}
