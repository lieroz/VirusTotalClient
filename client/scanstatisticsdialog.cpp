#include "scanstatisticsdialog.h"

#include <QStandardItemModel>
#include <QJsonObject>
#include <QDebug>
#include <QResizeEvent>


ScanStatisticsDialog::ScanStatisticsDialog(QWidget* parent) :
	QDialog(parent) {
	ui.setupUi(this);

	ui.listView->setFixedHeight(150);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void ScanStatisticsDialog::changeEvent(QEvent* e) {
	QDialog::changeEvent(e);

	switch (e->type()) {

		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			break;

		default:
			break;
	}
}


void ScanStatisticsDialog::fillListWithData(const QJsonObject& json_object) {
	QStandardItemModel* model{new QStandardItemModel{this}};

	model->setColumnCount(2);


}


void ScanStatisticsDialog::fillTableWithData(const QJsonObject& json_object) {
	QStandardItemModel* model{new QStandardItemModel{this}};

	model->setColumnCount(4);

	model->setHorizontalHeaderItem(0, new QStandardItem{QString{"Antivirus"}});
	model->setHorizontalHeaderItem(1, new QStandardItem{QString{"Result"}});
	model->setHorizontalHeaderItem(2, new QStandardItem{QString{"Update"}});
	model->setHorizontalHeaderItem(3, new QStandardItem{QString{"Version"}});

	auto i_keys = json_object["scans"].toObject().keys();
	auto i_values = json_object["scans"].toObject();
	size_t rows_amount{};

	for (auto i_key : i_keys) {
		size_t columns_amount{};

		model->insertRow(rows_amount);
		QStandardItem* item{new QStandardItem{QString{i_key}}};
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		model->setItem(rows_amount, columns_amount++, item);

		auto j_keys = i_values.value(i_key).toObject().keys();
		auto j_values = i_values.value(i_key).toObject();

		for (auto j_key : j_keys) {
			QString item_value{};

			if (j_key == "result") {
				continue;
			}

			if (j_values.value(j_key).isBool()) {

				if (j_values.value(j_key).toBool()) {
					item_value = "True";

				} else {
					item_value = "False";
				}

			} else if (j_values.value(j_key).isString()) {
				item_value = j_values.value(j_key).toString();
			}

			item = new QStandardItem{QString{item_value}};
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			model->setItem(rows_amount, columns_amount++, item);
		}

		++rows_amount;
	}

	ui.tableView->setModel(model);

	for (int i{}; i < 4; ++i) {
		ui.tableView->setColumnWidth(i, 200);
	}
}
