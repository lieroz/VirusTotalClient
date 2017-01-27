#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget* parent) :
	QDialog(parent) {
	ui.setupUi(this);

	dir_model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dir_model->setRootPath(root_path);

	ui.folderBrowserView->setModel(dir_model);

	file_model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
	file_model->setRootPath(root_path);

	ui.fileBrowserView->setModel(file_model);
}

void FileBrowser::changeEvent(QEvent* e) {
	QDialog::changeEvent(e);

	switch (e->type()) {
		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			break;

		default:
			break;
	}
}

void FileBrowser::on_folderBrowserView_clicked(const QModelIndex& index) {
	QString path = dir_model->fileInfo(index).absoluteFilePath();
	ui.fileBrowserView->setRootIndex(file_model->setRootPath(path));
}
