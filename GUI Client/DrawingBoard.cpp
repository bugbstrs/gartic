#include "DrawingBoard.h"

DrawingBoard::DrawingBoard(QWidget *parent)
	: QWidget(parent)
{
	setMouseTracking(true);
    changePenPropertiesTo(Qt::black, 2);
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event) {
    if (drawing) {
        currentPath.lineTo(event->pos());
        update();
    }
}

void DrawingBoard::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        currentPath = QPainterPath(event->pos());
        update();
    }
}


void DrawingBoard::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        paths.push_back(currentPath);
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

        painter.setPen(pen);
        for (const auto& path : paths) {
            painter.drawPath(path);
        }

        if (drawing) {
            painter.setPen(pen);
            painter.drawPath(currentPath);
        }
    }
}