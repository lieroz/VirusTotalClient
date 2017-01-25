#include "networkmanager.h"


void NetworkManager::scanFileRequest(const QString& absolute_file_path) {
	const QFileInfo file_info(absolute_file_path);
	QHttpMultiPart* multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);

	QHttpPart api_key_part;
	api_key_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"apikey\""));
	api_key_part.setBody(api_key);

	QHttpPart file_part;
	QMimeDatabase db;
	QMimeType mime_message = db.mimeTypeForFile(file_info);
	file_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mime_message.name()));
	file_part.setHeader(QNetworkRequest::ContentDispositionHeader,
						QVariant("form-data; name=\"file\"; filename=\"" + file_info.fileName() + "\""));

	QFile* file = new QFile(absolute_file_path);
	file->open(QIODevice::ReadOnly);
	file_part.setBodyDevice(file);
	file->setParent(multi_part);

	multi_part->append(api_key_part);
	multi_part->append(file_part);

	QNetworkRequest request(QUrl(api_address + "/file/scan"));
	network_manager->post(request, multi_part);
}


void NetworkManager::rescanFileRequest(const QString& resource) {
	QUrlQuery query_set;
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("resource", resource);

	QUrl post_params;
	post_params.setQuery(query_set);

	QByteArray post_data = post_params.toEncoded(QUrl::RemoveFragment);
	post_data.remove(0, 1);

	QNetworkRequest request(QUrl(api_address + "/file/rescan"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	network_manager->post(request, post_data);
}


void NetworkManager::retrieveFileReportRequest(const QString& resource) {
	QUrl url(api_address + "/file/report");

	QUrlQuery query_set;
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("resource", resource);

	url.setQuery(query_set.query());
	QNetworkRequest request(url);

	network_manager->get(request);
}


void NetworkManager::scanUrlRequest(const QString& url) {
	QUrlQuery query_set;
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("url", url);

	QUrl post_params;
	post_params.setQuery(query_set);

	QByteArray post_data = post_params.toEncoded(QUrl::RemoveFragment);
	post_data.remove(0, 1);

	QNetworkRequest request(QUrl(api_address + "/url/scan"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	network_manager->post(request, post_data);
}


void NetworkManager::retrieveUrlReportRequest(const QString& resource) {
	QUrlQuery query_set;
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("resource", resource);

	QUrl post_params;
	post_params.setQuery(query_set);

	QByteArray post_data = post_params.toEncoded(QUrl::RemoveFragment);
	post_data.remove(0, 1);

	QNetworkRequest request(QUrl(api_address + "/url/report"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	network_manager->post(request, post_data);
}


void NetworkManager::retrieveIpReportRequest(const QString& ip) {
	QUrl url(api_address + "/ip-address/report");

	QUrlQuery query_set;
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("ip", ip);

	url.setQuery(query_set.query());
	QNetworkRequest request(url);

	network_manager->get(request);
}


void NetworkManager::retrieveDomainReportRequest(const QString& domain) {
	QUrl url(api_address + "/domain/report");

	QUrlQuery query_set;
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("domain", domain);

	url.setQuery(query_set.query());
	QNetworkRequest request(url);

	network_manager->get(request);
}


void NetworkManager::requestFinished(QNetworkReply* reply) {
	qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	QByteArray raw_data = reply->readAll();
	QJsonObject json_object = QJsonDocument::fromJson(raw_data).object();

	qDebug() << json_object;
	qDebug() << json_object["scan_id"];

	QList<QByteArray> header_list = reply->rawHeaderList();

	for (auto header : header_list) {
		qDebug() << header << ":" << reply->rawHeader(header);
	}
}
