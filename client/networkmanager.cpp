#include "networkmanager.h"
#include "responses.h"
#include "status_codes.h"
#include "program_exceptions.h"
#include "scanstatisticsdialog.h"

#include <QMessageBox>
#include <QApplication>


void NetworkManager::scanFileRequest(const QString& absolute_file_path) {
	request_type = "file";
	const QFileInfo file_info{absolute_file_path};
	QHttpMultiPart* multi_part{new QHttpMultiPart(QHttpMultiPart::FormDataType)};

	QHttpPart api_key_part{};
	api_key_part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"apikey\""));
	api_key_part.setBody(api_key);

	QHttpPart file_part{};
	QMimeDatabase db{};
	QMimeType mime_message{db.mimeTypeForFile(file_info)};
	file_part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(mime_message.name()));
	file_part.setHeader(QNetworkRequest::ContentDispositionHeader,
						QVariant("form-data; name=\"file\"; filename=\"" + file_info.fileName() + "\""));

	QFile* file{new QFile{absolute_file_path}};

	try {

		if (!file->open(QIODevice::ReadOnly)) {
			throw FileDoesNotExistException();
		}

	} catch (std::exception& ex) {
		QMessageBox message_box{QMessageBox::Warning, "Warning", QObject::tr(ex.what()),
								QMessageBox::NoButton, 0, Qt::FramelessWindowHint};

		message_box.exec();
	}

	file_part.setBodyDevice(file);
	file->setParent(multi_part);

	multi_part->append(api_key_part);
	multi_part->append(file_part);

	QNetworkRequest request{QUrl{api_address + "/file/scan"}};
	network_manager->post(request, multi_part);
}


void NetworkManager::rescanFileRequest(const QString& resource) {
	QUrlQuery query_set{};
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("resource", resource);

	QUrl post_params{};
	post_params.setQuery(query_set);

	QByteArray post_data{post_params.toEncoded(QUrl::RemoveFragment)};
	post_data.remove(0, 1);

	QNetworkRequest request{QUrl{api_address + "/file/rescan"}};
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	network_manager->post(request, post_data);
}


void NetworkManager::retrieveFileReportRequest(const QString& resource) {
	QUrl url{api_address + "/file/report"};

	QUrlQuery query_set{};
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("resource", resource);

	url.setQuery(query_set.query());
	QNetworkRequest request{url};

	network_manager->get(request);
}


void NetworkManager::scanUrlRequest(const QString& url) {
	request_type = "url";
	QUrlQuery query_set{};
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("url", url);

	QUrl post_params{};
	post_params.setQuery(query_set);

	QByteArray post_data{post_params.toEncoded(QUrl::RemoveFragment)};
	post_data.remove(0, 1);

	QNetworkRequest request{QUrl{api_address + "/url/scan"}};
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	network_manager->post(request, post_data);
}


void NetworkManager::retrieveUrlReportRequest(const QString& resource) {
	QUrlQuery query_set{};
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("resource", resource);

	QUrl post_params{};
	post_params.setQuery(query_set);

	QByteArray post_data{post_params.toEncoded(QUrl::RemoveFragment)};
	post_data.remove(0, 1);

	QNetworkRequest request{QUrl{api_address + "/url/report"}};
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	network_manager->post(request, post_data);
}


void NetworkManager::retrieveIpReportRequest(const QString& ip) {
	QUrl url{api_address + "/ip-address/report"};

	QUrlQuery query_set{};
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("ip", ip);

	url.setQuery(query_set.query());
	QNetworkRequest request{url};

	network_manager->get(request);
}


void NetworkManager::retrieveDomainReportRequest(const QString& domain) {
	QUrl url{api_address + "/domain/report"};

	QUrlQuery query_set{};
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("domain", domain);

	url.setQuery(query_set.query());
	QNetworkRequest request{url};

	network_manager->get(request);
}


void NetworkManager::makeCommentRequest(const QString& resource, const QString& comment) {
	QUrlQuery query_set{};
	query_set.addQueryItem("apikey", api_key);
	query_set.addQueryItem("resource", resource);
	query_set.addQueryItem("comment", comment);

	QUrl post_params{};
	post_params.setQuery(query_set);

	QByteArray post_data{post_params.toEncoded(QUrl::RemoveFragment)};
	post_data.remove(0, 1);

	QNetworkRequest request{QUrl{api_address + "/comments/put"}};
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	network_manager->post(request, post_data);
}


void NetworkManager::requestFinished(QNetworkReply* reply) {
	try {
		http_status_code_t server_reply{static_cast<http_status_code_t>(
											reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt())};

		if (server_reply == OK) {

			QJsonObject json_object = QJsonDocument::fromJson(reply->readAll()).object();
			response_code_t response_code{static_cast<response_code_t>(json_object["response_code"].toInt())};
			std::string verbose_msg{json_object["verbose_msg"].toString().toStdString()};

			if (verbose_msg == "Scan request successfully queued, come back later for the report") {

				if (!is_active) {
					is_active = true;
					main_window = static_cast<MainWindow*>(QApplication::activeWindow());
					main_window->setDisabled(true);
					overlay_widget = new OverlayWidget{main_window};
				}

				QMessageBox message_box{QMessageBox::Information, "Information", QObject::tr(verbose_msg.c_str()),
										QMessageBox::NoButton, 0, Qt::FramelessWindowHint};
				message_box.exec();
			}

			if (response_code == ITEM_IS_PRESENT) {

				if (verbose_msg == "Scan finished, information embedded" ||
					verbose_msg == "Scan finished, scan information embedded in this object") {
					overlay_widget->setParent(0);
					delete overlay_widget;

					ScanStatisticsDialog* scan_statistics{new ScanStatisticsDialog};
					scan_statistics->fillListWithData(json_object);
					scan_statistics->fillTableWithData(json_object);
					scan_statistics->exec();

					main_window->setEnabled(true);

					return;
				}

				if (request_type == "file") {
					QTimer::singleShot(15000, this, [=] {
						retrieveFileReportRequest(json_object["resource"].toString());
					});

				} else if (request_type == "url") {
					QTimer::singleShot(15000, this, [=] {
						retrieveUrlReportRequest(json_object["resource"].toString());
					});
				}

			} else if (response_code == 0 && json_object["verbose_msg"].toInt() == 0) {

				if (json_object["verbose_msg"].toString().toStdString().empty()) {
					verbose_msg = "Item doesn't exist";
				}

				throw ItemDoesNotExistException(verbose_msg);

			} else {

				if (request_type == "file") {
					QTimer::singleShot(15000, this, [=] {
						retrieveFileReportRequest(json_object["resource"].toString());
					});

				} else if (request_type == "url") {
					QTimer::singleShot(15000, this, [=] {
						retrieveUrlReportRequest(json_object["resource"].toString());
					});
				}
			}

		} else if (server_reply == API_REQUEST_LIMIT_EXCEEDED) {
			throw PublicAPIRequestRateExceededException();

		} else if (server_reply == FORBIDDEN) {
			throw ForbiddenException();

		} else {
			throw UnknownHttpStatusCodeException();
		}

	} catch (std::exception& ex) {
		QMessageBox message_box{QMessageBox::Warning, "Warning", QObject::tr(ex.what()),
								QMessageBox::NoButton, 0, Qt::FramelessWindowHint};

		message_box.exec();
	}
}
