#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtNetwork>

class NetworkManager : public QObject {

		Q_OBJECT

	private:

		QNetworkAccessManager* manager;

	public:

		explicit NetworkManager();
		virtual ~NetworkManager() = default;

		void processRequest();

	public slots:

		void requestFinished(QNetworkReply*);
};

#endif // NETWORKMANAGER_H
