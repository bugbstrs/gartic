#include "DrawingBoard.h"
#include <thread>
#include <future>

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
    bool createdTop = false;
    bool createdBottom = false;
    bool createdLeft = false;
    bool createdRight = false;

    image.setPixelColor(startingPoint, colorToBeFilledWith);
    QPoint currentPointTop = pointToExecuteAt + QPoint(0, 1);
    QPoint currentPointBottom = pointToExecuteAt + QPoint(0, -1);
    QPoint currentPointLeft = pointToExecuteAt + QPoint(-1, 0);
    QPoint currentPointRight = pointToExecuteAt + QPoint(1, 0);

    std::thread topFill = std::thread(&DrawingBoard::FillTop, this, startingPoint + QPoint(0, 1), pointToExecuteAt + QPoint(0, 1), std::ref(currentPointTop), startingColor, colorToBeFilledWith);

    std::thread bottomFill = std::thread(&DrawingBoard::FillBottom, this, startingPoint + QPoint(0, -1), pointToExecuteAt + QPoint(0, -1), std::ref(currentPointBottom), startingColor, colorToBeFilledWith);

    std::thread leftFill = std::thread(&DrawingBoard::FillLeft, this, startingPoint + QPoint(-1, 0), pointToExecuteAt + QPoint(-1, 0), std::ref(currentPointLeft), startingColor, colorToBeFilledWith);
    
    std::thread rightFill = std::thread(&DrawingBoard::FillRight, this, startingPoint + QPoint( 1, 0), pointToExecuteAt + QPoint(1, 0), std::ref(currentPointRight),  startingColor, colorToBeFilledWith);

    while (true) {
        if (topFill.joinable() && !createdTop) {
            createdTop = true;
            topFill.join();
            std::thread newThread1(&DrawingBoard::FillBottom, this, currentPointBottom, currentPointBottom, std::ref(currentPointBottom), startingColor, colorToBeFilledWith);
            if (newThread1.joinable())
                newThread1.join();
            //newThread1.detach();
        }
        if (bottomFill.joinable() && !createdBottom) {
            createdBottom = true;
            bottomFill.join();
            std::thread newThread2(&DrawingBoard::FillTop, this, currentPointTop, currentPointTop, std::ref(currentPointTop), startingColor, colorToBeFilledWith);
            if (newThread2.joinable())
                newThread2.join();
            //newThread2.detach();
        }
        if (leftFill.joinable() && !createdLeft) {
            createdLeft = true;
            leftFill.join();
            std::thread newThread3(&DrawingBoard::FillRight, this, currentPointRight, currentPointRight, std::ref(currentPointRight), startingColor, colorToBeFilledWith);
            if (newThread3.joinable())
                newThread3.join();
            //newThread3.detach();
        }
        if (rightFill.joinable() && !createdRight) {
            createdRight = true;
            rightFill.join();
            std::thread newThread4(&DrawingBoard::FillLeft, this, currentPointLeft, currentPointLeft, std::ref(currentPointLeft), startingColor, colorToBeFilledWith);
            if (newThread4.joinable())
                newThread4.join();
            //newThread4.detach();
        }
        if (!topFill.joinable() && !bottomFill.joinable() && !leftFill.joinable() && !rightFill.joinable())
            break;
    }
    

    /*update();*/
}

void DrawingBoard::FillTop(QPoint startingPoint, QPoint pointToExecuteAt, QPoint& globalCurrentPos, QColor startingColor, QColor colorToBeFilledWith)
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

        if (image.pixelColor(currentPoint) != startingColor || !imageRect.contains(currentPoint) || image.pixelColor(currentPoint) == colorToBeFilledWith)
            continue;

        image.setPixelColor(currentPoint, colorToBeFilledWith);
        globalCurrentPos = currentPoint + QPoint(0, 1);
        pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        /*pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));*/
    }
    update();
}

void DrawingBoard::FillBottom(QPoint startingPoint, QPoint pointToExecuteAt, QPoint& globalCurrentPos, QColor startingColor, QColor colorToBeFilledWith)
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

        if (image.pixelColor(currentPoint) != startingColor || !imageRect.contains(currentPoint) || image.pixelColor(currentPoint) == colorToBeFilledWith)
            continue;

        image.setPixelColor(currentPoint, colorToBeFilledWith);
        globalCurrentPos = currentPoint + QPoint(0, -1);
        pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
        /*pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));*/
    }
    update();
}

void DrawingBoard::FillLeft(QPoint startingPoint, QPoint pointToExecuteAt, QPoint& globalCurrentPos, QColor startingColor, QColor colorToBeFilledWith)
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

        if (image.pixelColor(currentPoint) != startingColor || !imageRect.contains(currentPoint) || image.pixelColor(currentPoint) == colorToBeFilledWith)
            continue;

        image.setPixelColor(currentPoint, colorToBeFilledWith);
        globalCurrentPos = currentPoint + QPoint(0, -1);
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
        /*pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));*/
    }
    update();
}

void DrawingBoard::FillRight(QPoint startingPoint, QPoint pointToExecuteAt, QPoint& globalCurrentPos, QColor startingColor, QColor colorToBeFilledWith)
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

        if (image.pixelColor(currentPoint) != startingColor || !imageRect.contains(currentPoint) || image.pixelColor(currentPoint) == colorToBeFilledWith)
            continue;

        image.setPixelColor(currentPoint, colorToBeFilledWith);
        globalCurrentPos = currentPoint + QPoint(0, -1);
        pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
        /*pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));*/
    }
    update();
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