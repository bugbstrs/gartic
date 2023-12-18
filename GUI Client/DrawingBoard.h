#pragma once

#include <QWidget>
#include <qimage.h>
#include <QMouseEvent>
#include <qpainter.h>
#include <qpainterpath.h>
#include <queue>
#include <atomic>
#include <stack>
#include <thread>

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
	void ToggleFill(bool value);
	void EnablePencil();
	void UndoLastPath();
	void ClearCanvas();


protected:
	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event);

private:
	void FloodFill(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);
	void GenericFill(QPoint startingPoint, QPoint& pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith, bool& done);
	void DrawStartingPixels(QPoint startingPoint, QPoint pointToExecuteAt, int radius, QColor startingColor, QColor colorToBeFilledWith, std::vector <std::thread>& threads);

private:
	bool firstPaint = true;
	bool mouseOverBoard = false;
	bool drawing = false;
	bool erasing = false;
	bool fillEnabled = false;
	bool undo = false;
	QPen pen;
	QColor lastColor;
	QColor eraserColor;
	QPoint lastMousePos;
	QPainterPath currentPath;
	std::vector<std::pair<QPainterPath, QPen>> paths;
	std::vector<QImage>images;
	QImage image;
	std::unordered_map<std::string, bool> availableDirections;
};
