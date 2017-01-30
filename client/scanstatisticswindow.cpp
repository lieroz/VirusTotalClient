#include "scanstatisticswindow.h"

#include <QDebug>


ScanStatisticswindow::ScanStatisticswindow() {
	this->setReadOnly(true);
}


void ScanStatisticswindow::fillWindow(const QJsonObject& json_object) {
	auto antiviruses = json_object["scans"].toObject().keys();
	auto values = json_object["scans"].toObject();

	for (auto antivirus : antiviruses) {
		this->appendPlainText(antivirus + " :");
		this->appendPlainText("-----------------------------------------------------");
		QString text{};

		auto keys = values.value(antivirus).toObject().keys();

		for (auto key : keys) {
			text.append(key + " : ");

			if (values.value(antivirus).toObject().value(key).isBool()) {
				QString value{};

				if (values.value(antivirus).toObject().value(key).toBool()) {
					value = "true";
				} else {
					value = "false";
				}

				text.append(value + "; ");

			} else if (values.value(antivirus).toObject().value(key).isNull()) {

				QString value{};

				if (values.value(antivirus).toObject().value(key).toInt() == 0) {
					value = "null";
				} else {
					value = "not_null";
				}

				text.append(value + "; ");

			} else if (values.value(antivirus).toObject().value(key).isString()) {
				text.append(values.value(antivirus).toObject().value(key).toString() + "; ");
			}
		}

		this->appendPlainText(text + '\n');
	}
}
