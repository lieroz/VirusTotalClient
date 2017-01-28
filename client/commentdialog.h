#ifndef COMMENTDIALOG_H
#define COMMENTDIALOG_H

#include "ui_commentdialog.h"


class CommentDialog : public QDialog {

		Q_OBJECT

	private:

		Ui::CommentDialog ui;

	public:

		explicit CommentDialog(QWidget* parent = 0);

	protected:

		void changeEvent(QEvent* e);

	private slots:

		void on_submitButton_clicked();
};


#endif // COMMENTDIALOG_H
