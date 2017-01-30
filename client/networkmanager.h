#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtNetwork>
#include <QDialog>


class NetworkManager : public QObject {

		Q_OBJECT

	private:

		QString api_address{"https://www.virustotal.com/vtapi/v2"};
		QByteArray api_key{"0c1c7087646c9351505ff1fc652f2de641a389269ddd72c607eeb96eb7e6f204"};
		QNetworkAccessManager* network_manager{new QNetworkAccessManager(this)};

	public:

		explicit NetworkManager() {
			connect(network_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
		}

		virtual ~NetworkManager() = default;

		void scanFileRequest(const QString&);
		void rescanFileRequest(const QString&);
		void retrieveFileReportRequest(const QString&);

		void scanUrlRequest(const QString&);
		void retrieveUrlReportRequest(const QString&);

		void retrieveIpReportRequest(const QString&);
		void retrieveDomainReportRequest(const QString&);
		void makeCommentRequest(const QString&, const QString&);

	private slots:

		void requestFinished(QNetworkReply*);
};


#endif // NETWORKMANAGER_H
