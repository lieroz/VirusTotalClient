#ifndef SCANSTATISTICSWINDOW_H
#define SCANSTATISTICSWINDOW_H

#include <QPlainTextEdit>
#include <QJsonObject>

class ScanStatisticswindow : public QPlainTextEdit {

		Q_OBJECT

	public:

		explicit ScanStatisticswindow();
		virtual ~ScanStatisticswindow() = default;

		void fillWindow(const QJsonObject&);
};

#endif // SCANSTATISTICSWINDOW_H
