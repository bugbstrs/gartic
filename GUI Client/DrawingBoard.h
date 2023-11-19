#pragma once

#include <QWidget>
#include <qpainter.h>
#include <QMouseEvent>
#include <qpainterpath.h>

class DrawingBoard : public QWidget
{
	Q_OBJECT

public:
	//Constructors
	DrawingBoard(QWidget* parent = nullptr);

	//Functionality
	void changePenPropertiesTo(QColor color, int width);
	void changePenColor(QColor color);


protected:
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;


private:
	bool firstPaint = true;
	bool mouseOverBoard = false;
	bool drawing = false;
	QPen pen;
	QPainterPath currentPath;
	QList<QPainterPath> paths;
	std::vector<QPointF> circles;
};
