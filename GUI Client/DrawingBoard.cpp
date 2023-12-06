#include "DrawingBoard.h"
#include <thread>

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
    if (event->button() == Qt::LeftButton && !readyToFill) {
        drawing = true;
        currentPath = QPainterPath(event->pos());
        update();
    }
    else FloodFill(event->pos(), event->pos(), image.pixelColor(event->pos()), pen.color());
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        paths.push_back({ currentPath, pen });
        update();
    }
}

void DrawingBoard::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    image = QImage(size(), QImage::Format_ARGB32);
    image.fill(Qt::white);
}

void DrawingBoard::FloodFill(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith)
{

    std::thread topFill(&DrawingBoard::FillTop, this, startingPoint, pointToExecuteAt, startingColor, colorToBeFilledWith);

    std::thread bottomFill(&DrawingBoard::FillBottom, this, startingPoint + QPoint(0, -1), pointToExecuteAt + QPoint(0, -1), startingColor, colorToBeFilledWith);

    topFill.join();
    bottomFill.join();

    update();
}

void DrawingBoard::FillTop(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith)
{
    if (!image.rect().contains(pointToExecuteAt))
        return;

    if (image.pixelColor(pointToExecuteAt) != startingColor)
        return;

    QPoint currentPoint;
    QRect imageRect = image.rect();
    std::queue<QPoint> pointsQueue;
    pointsQueue.push(pointToExecuteAt);

    while (!pointsQueue.empty()) {
        currentPoint = pointsQueue.front();
        pointsQueue.pop();

        if (currentPoint.y() < startingPoint.y() || image.pixelColor(currentPoint) != startingColor || !imageRect.contains(currentPoint) || image.pixelColor(currentPoint) == colorToBeFilledWith)
            continue;

        image.setPixelColor(currentPoint, colorToBeFilledWith);

        pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
    }
}

void DrawingBoard::FillBottom(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith)
{
    if (!image.rect().contains(pointToExecuteAt))
        return;

    if (image.pixelColor(pointToExecuteAt) != startingColor)
        return;

    QPoint currentPoint;
    QRect imageRect = image.rect();
    std::queue<QPoint> pointsQueue;
    pointsQueue.push(pointToExecuteAt);

    while (!pointsQueue.empty()) {
        currentPoint = pointsQueue.front();
        pointsQueue.pop();

        if (currentPoint.y() > startingPoint.y() || image.pixelColor(currentPoint) != startingColor || !imageRect.contains(currentPoint) || image.pixelColor(currentPoint) == colorToBeFilledWith)
            continue;

        image.setPixelColor(currentPoint, colorToBeFilledWith);

        pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
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

void DrawingBoard::ToggleEraser(bool value)
{
    if (value) {
        pen.setColor(Qt::white);
    }
    readyToFill = false;
    update();
}

void DrawingBoard::UndoLastPath()
{
    paths.pop_back();
    update();
}

void DrawingBoard::Fill()
{
    readyToFill = true;
}

void DrawingBoard::ClearCanvas()
{
    currentPath = QPainterPath();
    paths.clear();
    image.fill(Qt::white);
    update();
}

void DrawingBoard::paintEvent(QPaintEvent* event) {
    if (firstPaint) {
        setAutoFillBackground(true);
        firstPaint = false;
    }
    else {
        QPainter imagePainter(this);
        imagePainter.drawImage(0, 0, image);

        QPainter painter(&image);

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