#include "DrawingBoard.h"

DrawingBoard::DrawingBoard(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);
    changePenPropertiesTo(Qt::black, 2);
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event) {
    if (drawing) {
        currentLine.first.push_back(event->pos());
        update();
    }
}

void DrawingBoard::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        currentLine.first.push_back(event->pos());
        currentLine.second = pen.color();
        update();
    }
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        currentLine.first.push_back(event->pos());
        coordinates.push_back(currentLine);
        currentLine.first.clear();
        update();
    }
}

void DrawingBoard::changePenPropertiesTo(QColor color, int width)
{
    pen.setColor(color);
    pen.setWidth(width);
}

void DrawingBoard::changePenColor(QColor color)
{
    pen.setColor(color);
}


void DrawingBoard::paintEvent(QPaintEvent* event) {
    if (firstPaint) {
        setAutoFillBackground(true);
        firstPaint = false;
    }
    else {
        QPainter painter(this);
        pen.setColor(currentLine.second);
        painter.setPen(pen);
        for (int index = 1; index < currentLine.first.size(); index++)
            painter.drawLine(currentLine.first[index - 1], currentLine.first[index]);

        for (auto& drawnLine : coordinates) {
            pen.setColor(drawnLine.second);
            painter.setPen(pen);
            for (int index = 1; index < drawnLine.first.size(); index++) {
                painter.drawLine(drawnLine.first[index - 1], drawnLine.first[index]);
            }
        }
    }
}