#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {

		Q_OBJECT

	public:

		explicit MainWindow(QWidget* parent = 0);
		virtual ~MainWindow() = default;

	protected:

		void changeEvent(QEvent* e);

	private slots:

		void on_pushButton_clicked();

	private:

		Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
