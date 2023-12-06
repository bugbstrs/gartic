#pragma once

#include <QWidget>
#include <qimage.h>
#include <QMouseEvent>
#include <qpainter.h>
#include <qpainterpath.h>
#include <queue>
#include <stack>

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
	void ToggleEraser(bool value);
	void UndoLastPath();
	void Fill();
	void ClearCanvas();


protected:
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event);

private:
	void FloodFill(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);
	void FillTop(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);
	void FillBottom(QPoint startingPoint,QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);

private:
	bool firstPaint = true;
	bool mouseOverBoard = false;
	bool drawing = false;
	bool eraserEnabled = false;
	bool readyToFill;
	QPen pen;
	QPainterPath currentPath;
	std::vector<std::pair<QPainterPath, QPen>> paths;
	QImage image;
};
