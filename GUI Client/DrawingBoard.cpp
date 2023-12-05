#include "DrawingBoard.h"

DrawingBoard::DrawingBoard(QWidget* parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    ChangePenPropertiesTo(Qt::black, 2);
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
        paths.push_back({ currentPath, pen });
        update();
    }
}

void DrawingBoard::ChangePenPropertiesTo(QColor color, int width)
{
    pen.setColor(color);
    pen.setWidth(width);
    pen.setCapStyle(Qt::RoundCap);
}

void DrawingBoard::ChangePenColor(QColor color)
{
    pen.setColor(color);
}

void DrawingBoard::ChangePenWidth(int width)
{
    pen.setWidth(width);
}

void DrawingBoard::ClearCanvas()
{
    currentPath = QPainterPath();
    paths.clear();
    update();
}

void DrawingBoard::paintEvent(QPaintEvent* event) {
    if (firstPaint) {
        setAutoFillBackground(true);
        firstPaint = false;
    }
    else {
        QPainter painter(this);

        for (auto& path : paths) {
            painter.setPen(path.second);
            painter.drawPath(path.first);
        }

        if (drawing) {
            painter.setPen(pen);
            painter.drawPath(currentPath);
        }
    }
}