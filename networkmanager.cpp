#include "networkmanager.h"

NetworkManager::NetworkManager() {
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

void NetworkManager::processRequest() { // TODO
	manager->get(QNetworkRequest(QUrl("https://www.virustotal.com/")));
}

void NetworkManager::requestFinished(QNetworkReply* reply) {
	QString data = reply->readAll().trimmed();
	qDebug() << data;
}
