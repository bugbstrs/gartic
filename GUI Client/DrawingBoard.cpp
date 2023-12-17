#include "DrawingBoard.h"
#include <thread>
#include <future>

DrawingBoard::DrawingBoard(QWidget* parent)
    : QWidget{ parent },
    eraserColor{Qt::white}
{
    setMouseTracking(true);
    ChangePenPropertiesTo(Qt::black, 2);
}

void DrawingBoard::mousePressEvent(QMouseEvent* event) {
    images.push_back(image);
    if (event->button() == Qt::LeftButton && !fillEnabled) {
        drawing = true;
        currentPath = QPainterPath(event->pos());
        update();
    }
    if (fillEnabled) {
        QPoint mouseRegisteredPosition = event->pos() + QPoint(-12, 10);
        FloodFill(mouseRegisteredPosition, mouseRegisteredPosition, image.pixelColor(mouseRegisteredPosition), pen.color());
    }
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event) {
    if (drawing) {
        currentPath.lineTo(event->pos());
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

void DrawingBoard::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    image = QImage(size(), QImage::Format_ARGB32);
    image.fill(Qt::white);
}

void DrawingBoard::ChangePenPropertiesTo(QColor color, int width)
{
    lastColor = color;
    pen.setColor(color);
    pen.setWidth(width);
    pen.setCapStyle(Qt::RoundCap);
}

void DrawingBoard::ChangePenColor(QColor color)
{
    lastColor = color;
    pen.setColor(color);
}

void DrawingBoard::ChangePenWidth(int width)
{
    pen.setWidth(width);
}

void DrawingBoard::ToggleEraser(bool value)
{
    if (value)
        pen.setColor(eraserColor);
    else pen.setColor(lastColor);
}

void DrawingBoard::ToggleFill(bool value)
{
    fillEnabled = value;
}

void DrawingBoard::EnablePencil()
{
    pen.setColor(lastColor);
}

void DrawingBoard::UndoLastPath()
{
    if (!images.empty()) {
        image = images.back();
        images.pop_back();
    }
    else image.fill(Qt::white);
    update();
}

void DrawingBoard::ClearCanvas()
{
    currentPath = QPainterPath();
    image.fill(Qt::white);
    images.clear();
    update();
}

void DrawingBoard::FloodFill(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith)
{
    bool topDone = false;
    bool bottomDone = false;
    bool leftDone = false;
    bool rightDone = false;

    image.setPixelColor(startingPoint, colorToBeFilledWith);

    QPoint currentPointTop = pointToExecuteAt + QPoint(0, 1);
    QPoint currentPointBottom = pointToExecuteAt + QPoint(0, -1);
    QPoint currentPointLeft = pointToExecuteAt + QPoint(-1, 0);
    QPoint currentPointRight = pointToExecuteAt + QPoint(1, 0);

    int centerX = startingPoint.x();
    int centerY = startingPoint.y();
    int radius1 = 25;
    int radius2 = 26;

    std::vector <std::thread> threads;

    // Create the diamond shape
    for (int i = -radius2; i <= radius2; i++) {
        for (int j = -radius2; j <= radius2; j++) {
            int x = centerX + i;
            int y = centerY + j;
            if (image.pixelColor(QPoint(x, y)) != startingColor && image.pixelColor(QPoint(x, y)) != colorToBeFilledWith)
                break;
            double distance = sqrt(i * i + j * j);
            QPoint pointToExecuteAt(x, y);
            if (distance >= radius1 && distance <= radius2) {
                threads.emplace_back(std::thread(&DrawingBoard::GenericFill, this, QPoint(x, y), std::ref(pointToExecuteAt), startingColor, colorToBeFilledWith, std::ref(availableDirections["topDone"])));
            }
        }
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

void DrawingBoard::GenericFill(QPoint startingPoint, QPoint& pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith, bool& done)
{
    if (image.pixelColor(pointToExecuteAt) != startingColor)
        return;

    QPoint currentPoint;
    QRect imageRect = image.rect();
    std::queue<QPoint> pointsQueue;
    pointsQueue.push(pointToExecuteAt);

    while (!pointsQueue.empty()) {
        currentPoint = pointsQueue.front();
        pointsQueue.pop();

        if (image.pixelColor(currentPoint) != startingColor || image.pixelColor(currentPoint) == colorToBeFilledWith)
            continue;

        image.setPixelColor(currentPoint, colorToBeFilledWith);

        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
        pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
    }
    done = true;
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

        if (drawing) {
            painter.setPen(pen);
            painter.drawPath(currentPath);
        }
    }
}
