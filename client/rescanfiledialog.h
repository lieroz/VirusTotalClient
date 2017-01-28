#ifndef RESCANFILEDIALOG_H
#define RESCANFILEDIALOG_H

#include "ui_rescanfiledialog.h"

class RescanFileDialog : public QDialog
{
		Q_OBJECT

	private:

		Ui::RescanFileDialog ui;

	public:

		explicit RescanFileDialog(QWidget *parent = 0);

	protected:

		void changeEvent(QEvent *e);

	private slots:

		void on_submitButton_clicked();
};

#endif // RESCANFILEDIALOG_H
