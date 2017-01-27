#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include "ui_filebrowser.h"

#include <QFileSystemModel>


class FileBrowser : public QDialog {

		Q_OBJECT

	private:

		Ui::FileBrowser ui{};
		QFileSystemModel* dir_model{new QFileSystemModel(this)};
		QFileSystemModel* file_model{new QFileSystemModel(this)};
		QString root_path{};

		static QString absolute_file_path;

	public:

		explicit FileBrowser(QWidget* parent = 0);

		const static QString getFilePath() {
			return absolute_file_path;
		}

		void setFilePath(const QString& path) {
			absolute_file_path = path;
		}

	protected:

		void changeEvent(QEvent* e);

	private slots:

		void on_folderBrowserView_clicked(const QModelIndex& index);
		void on_fileBrowserView_clicked(const QModelIndex &index);
};

#endif // FILEBROWSER_H
