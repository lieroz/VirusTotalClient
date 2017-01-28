#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QLabel>
#include <QMovie>


class OverlayWidget : public QWidget {
	private:

		QLabel* label;
		QWidget* parent_widget;

	public:

		explicit OverlayWidget(QWidget* parent = 0);

	protected:

		bool eventFilter(QObject*, QEvent*) override;
		bool event(QEvent*) override;
		void paintEvent(QPaintEvent*) override;

	private:

		void newParent();
};


#endif // OVERLAYWIDGET_H
