#ifndef SCANSTATISTICSDIALOG_H
#define SCANSTATISTICSDIALOG_H

#include "ui_scanstatisticsdialog.h"


class ScanStatisticsDialog : public QDialog {

		Q_OBJECT

	private:

		Ui::ScanStatisticsDialog ui;

	public:

		explicit ScanStatisticsDialog(QWidget* parent = 0);
		virtual ~ScanStatisticsDialog() = default;

		void fillTableWithData(const QJsonObject&);
		void fillListWithData(const QJsonObject&);

	protected:

		void changeEvent(QEvent* e);
};


#endif // SCANSTATISTICSDIALOG_H
