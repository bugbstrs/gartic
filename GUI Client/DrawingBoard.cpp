#include "DrawingBoard.h"

DrawingBoard::DrawingBoard(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);
    changePenPropertiesTo(Qt::black, 4);
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event) {
    if (drawing && event->pos() != lastCoordinates) {
        currentLine.pathCoordinates.push_back(event->pos());
        lastCoordinates = event->pos();
        update();
    }
}

void DrawingBoard::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        currentLine.pathCoordinates.push_back(event->pos());
        currentLine.color = pen.color();
        currentLine.width = pen.width();
        update();
    }
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        currentLine.pathCoordinates.push_back(event->pos());
        drawnLines.push_back(currentLine);
        currentLine.pathCoordinates.clear();
        update();
    }
}

void DrawingBoard::changePenPropertiesTo(QColor color, int width)
{
    currentLine.color = color;
    currentLine.width = width;
    pen.setCapStyle(Qt::RoundCap);
}

void DrawingBoard::changePenColor(QColor color)
{
    pen.setColor(color);
}

void DrawingBoard::changePenWidth(int width)
{
    pen.setWidth(width);
}


void DrawingBoard::paintEvent(QPaintEvent* event) {
    if (firstPaint) {
        setAutoFillBackground(true);
        firstPaint = false;
    }
    else {
        QPainter painter(this);

        for (auto& drawnLine : drawnLines) {
            pen.setColor(drawnLine.color);
            pen.setWidth(drawnLine.width);
            painter.setPen(pen);
            for (int index = 1; index < drawnLine.pathCoordinates.size(); index++) {
                painter.drawLine(drawnLine.pathCoordinates[index - 1], drawnLine.pathCoordinates[index]);
            }
        }
        pen.setColor(currentLine.color);
        pen.setWidth(currentLine.width);
        painter.setPen(pen);
        for (int index = 1; index < currentLine.pathCoordinates.size(); index++) {
            painter.drawLine(currentLine.pathCoordinates[index - 1], currentLine.pathCoordinates[index]);
        }
    }
}