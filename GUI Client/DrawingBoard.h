#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <qpainter.h>
#include <qpainterpath.h>

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
	void ToggleEraser();
	void UndoLastPath();
	void Fill();
	void ClearCanvas();


protected:
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	bool firstPaint = true;
	bool mouseOverBoard = false;
	bool drawing = false;
	bool eraserEnabled = false;
	QPen pen;
	QPainterPath currentPath;
	std::vector<std::pair<QPainterPath, QPen>> paths;
};
