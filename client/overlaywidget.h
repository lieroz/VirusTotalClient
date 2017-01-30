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
		QMovie* movie;
		QWidget* parent_widget;

	public:

		explicit OverlayWidget(QWidget* parent = 0);
		virtual ~OverlayWidget();

	protected:

		bool eventFilter(QObject*, QEvent*) override;
		bool event(QEvent*) override;

	private:

		void newParent();
};


#endif // OVERLAYWIDGET_H
