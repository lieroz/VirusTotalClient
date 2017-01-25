#include "networkmanager.h"
#include <stdio.h>

NetworkManager::NetworkManager() {
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply*)));
}

void NetworkManager::processRequest() {
	QNetworkRequest request(QUrl("https://www.virustotal.com/vtapi/v2/url/scan"));

	QUrlQuery query;
	query.addQueryItem("apikey", "0c1c7087646c9351505ff1fc652f2de641a389269ddd72c607eeb96eb7e6f204");
	query.addQueryItem("url", "http://www.virustotal.com");

	QUrl params;
	params.setQuery(query);

	qDebug() << params;

	QByteArray data = params.toEncoded(QUrl::RemoveFragment);
	data.remove(0, 1);

	qDebug() << data;

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	manager->post(request, data);
}

void NetworkManager::requestFinished(QNetworkReply* reply) {
	QByteArray raw_data = reply->readAll();
	QJsonObject json_object = QJsonDocument::fromJson(raw_data).object();

	qDebug() << json_object;
	qDebug() << json_object["scan_id"];

	QList<QByteArray> header_list = reply->rawHeaderList();

	for (auto header : header_list) {
		qDebug() << header << ":" << reply->rawHeader(header);
	}
}
