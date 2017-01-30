#include "overlaywidget.h"

#include <QResizeEvent>
#include <QPainter>
#include <QLabel>
#include <QMovie>


OverlayWidget::OverlayWidget(QWidget* parent) :
	QWidget{parent}, parent_widget{parent} {
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_TranslucentBackground);

	newParent();

	label = new QLabel;
	label->setParent(parent);
	label->setAlignment(Qt::AlignAbsolute);
	label->move(parent_widget->rect().center() - QPoint{50, 50});

	movie = new QMovie{":/MyFiles/Files/test.gif"};
	movie->setParent(label);
	label->setMovie(movie);
	label->show();
	movie->start();
}


OverlayWidget::~OverlayWidget() {
	movie->stop();
	delete movie;
	delete label;
}


bool OverlayWidget::eventFilter(QObject* object, QEvent* event) {
	if (object == parent()) {

		if (event->type() == QEvent::Resize) {
			QResizeEvent* resize_event{static_cast<QResizeEvent*>(event)};
			this->resize(resize_event->size());
			label->move(parent_widget->rect().center() - QPoint{50, 50});

		} else if (event->type() == QEvent::ChildAdded) {
			raise();
		}
	}

	return QWidget::eventFilter(object, event);
}


bool OverlayWidget::event(QEvent* event) {
	if (event->type() == QEvent::ParentAboutToChange) {

		if (parent()) {
			parent()->removeEventFilter(this);
		}

	} else if (event->type() == QEvent::ParentChange) {
		newParent();
	}

	return QWidget::event(event);
}


void OverlayWidget::newParent() {
	if (parent() == nullptr) {
		return;
	}

	parent()->installEventFilter(this);
	raise();
}
