#include "scanstatisticsdialog.h"

#include <QStandardItemModel>
#include <QJsonObject>
#include <QDebug>
#include <QResizeEvent>


ScanStatisticsDialog::ScanStatisticsDialog(QWidget* parent) :
	QDialog(parent) {
	ui.setupUi(this);

	ui.headerView->setFixedHeight(150);
	ui.headerView->horizontalHeader()->setStretchLastSection(true);
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
	QStandardItemModel* model{new QStandardItemModel{4, 2, this}};

	model->setHorizontalHeaderItem(0, new QStandardItem{QString{"Object"}});
	model->setHorizontalHeaderItem(1, new QStandardItem{QString{"Content"}});

	QStandardItem* item{};

	item = new QStandardItem{QString{"MD5"}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(0, 0, item);

	item = new QStandardItem{QString{json_object["md5"].toString()}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(0, 1, item);

	item = new QStandardItem{QString{"SHA256"}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(1, 0, item);

	item = new QStandardItem{QString{json_object["sha256"].toString()}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(1, 1, item);

	item = new QStandardItem{QString{"Analysis date"}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(2, 0, item);

	item = new QStandardItem{QString{json_object["scan_date"].toString()}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(2, 1, item);

	item = new QStandardItem{QString{"Total"}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(3, 0, item);

	item = new QStandardItem{QString{std::to_string(json_object["total"].toInt()).c_str()}};
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	model->setItem(3, 1, item);

	ui.headerView->setModel(model);
	ui.headerView->setColumnWidth(0, 200);
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
}
