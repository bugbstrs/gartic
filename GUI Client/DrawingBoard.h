#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <qpainter.h>

class DrawingBoard : public QWidget
{
	Q_OBJECT

public:
	//Constructors
	DrawingBoard(QWidget* parent = nullptr);

	//Functionality
	void ChangePenPropertiesTo(QColor color, int width);
	void ChangePenColor(QColor color);
	void ChangePenWidth(int width);
	void ClearCanvas();


protected:
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	struct DrawnLine {
		std::vector<QPointF> pathCoordinates;
		QColor color;
		int width;
	};

private:
	bool firstPaint = true;
	bool mouseOverBoard = false;
	bool drawing = false;
	QPen pen;
	DrawnLine currentLine;
	std::vector<DrawnLine> drawnLines;
	QPointF lastCoordinates;
};
