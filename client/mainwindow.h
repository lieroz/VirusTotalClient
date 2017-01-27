#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"


class MainWindow : public QMainWindow {

		Q_OBJECT

	private:

		Ui::MainWindow ui;

	public:

		explicit MainWindow(QWidget* parent = 0);
		virtual ~MainWindow() = default;

	protected:

		void changeEvent(QEvent* e);

	private slots:

		void on_scanButton_clicked();

		void on_fileRadioButton_clicked();
		void on_urlRadioButton_clicked();
		void on_searchRadioButton_clicked();

		void on_uploadButton_clicked();
		void on_rescanButton_clicked();
};


#endif // MAINWINDOW_H
