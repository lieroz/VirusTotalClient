#include "filebrowser.h"


QString FileBrowser::absolute_file_path{};


FileBrowser::FileBrowser(QWidget* parent) :
	QDialog(parent) {
	ui.setupUi(this);

	dir_model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	dir_model->setRootPath(root_path);

	ui.folderBrowserView->setModel(dir_model);
	ui.folderBrowserView->setColumnWidth(0, 300);

	file_model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
	file_model->setRootPath(root_path);

	ui.fileBrowserView->setModel(file_model);

	ui.splitter->setSizes({850, 350});
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

void FileBrowser::on_fileBrowserView_clicked(const QModelIndex& index) {
	absolute_file_path = file_model->fileInfo(index).absoluteFilePath();
	this->close();
}
