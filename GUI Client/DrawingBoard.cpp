#include "DrawingBoard.h"

DrawingBoard::DrawingBoard(QWidget* parent)
    : QWidget{ parent },
    eraserColor { Qt::white }
{
    setMouseTracking(true);
    ChangePenPropertiesTo(Qt::black, 4);
}

void DrawingBoard::mousePressEvent(QMouseEvent* event)
{
    if (isChoosingWord)
        return;
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

void DrawingBoard::mouseMoveEvent(QMouseEvent* event)
{
    if (drawing) {
        currentPath.lineTo(event->pos());
        update();
    }
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event)
{
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

void DrawingBoard::ChangePenPropertiesTo(QColor color, int width) noexcept
{
    lastColor = color;
    pen.setColor(color);
    pen.setWidth(width);
    pen.setCapStyle(Qt::RoundCap);
}

void DrawingBoard::ChangePenColor(QColor color) noexcept
{
    lastColor = color;
    pen.setColor(color);
}

void DrawingBoard::ChangePenWidth(int width) noexcept
{
    pen.setWidth(width);
}

void DrawingBoard::SetIsChoosingWord(bool value)
{
    isChoosingWord = value;
}

void DrawingBoard::ToggleEraser(bool value) noexcept
{
    if (value)
        pen.setColor(eraserColor);
    else pen.setColor(lastColor);
}

void DrawingBoard::ToggleFill(bool value) noexcept
{
    fillEnabled = value;
}

void DrawingBoard::EnablePencil() noexcept
{
    pen.setColor(lastColor);
}

void DrawingBoard::UndoLastPath() noexcept
{
    if (!images.empty()) {
        image = images.back();
        images.pop_back();
    }
    else image.fill(Qt::white);
    update();
}

void DrawingBoard::ClearCanvas() noexcept
{
    currentPath = QPainterPath();
    image.fill(Qt::white);
    images.clear();
    update();
}

void DrawingBoard::ResetBoard() noexcept
{
    isChoosingWord = false;
    drawing = false;
    fillEnabled = false;
    lastColor = kDefaultPenColor;

    ChangePenPropertiesTo(kDefaultPenColor, kDefaultPenWidth);
    currentPath = QPainterPath();
    paths.clear();
    image.fill(Qt::white);
    images.clear();
}

void DrawingBoard::FloodFill(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith)
{
    std::vector <std::thread> threads;
    DrawStartingPixels(startingPoint, pointToExecuteAt, startingColor, colorToBeFilledWith, threads);
    for (auto& thread : threads) {
        thread.join();
    }
    update();
}

void DrawingBoard::DrawStartingPixels(const QPoint& startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith, std::vector<std::thread>& threads)
{
    if (image.pixelColor(pointToExecuteAt) != startingColor || image.pixelColor(pointToExecuteAt) == colorToBeFilledWith)
        return;

    double distance = std::sqrt(std::pow(pointToExecuteAt.x() - startingPoint.x(), 2) + std::pow(pointToExecuteAt.y() - startingPoint.y(), 2));

    if (distance <= kCircleRadius) {
        if (distance >= kCircleRadius - 1) {
            threads.emplace_back(std::thread(&DrawingBoard::GenericFill, this, pointToExecuteAt, std::ref(pointToExecuteAt), startingColor, colorToBeFilledWith));
        }
        else {
            image.setPixelColor(pointToExecuteAt, colorToBeFilledWith);
        }

        DrawStartingPixels(startingPoint, pointToExecuteAt + QPoint(1, 0), startingColor, colorToBeFilledWith, threads);
        DrawStartingPixels(startingPoint, pointToExecuteAt + QPoint(-1, 0), startingColor, colorToBeFilledWith, threads);
        DrawStartingPixels(startingPoint, pointToExecuteAt + QPoint(0, 1), startingColor, colorToBeFilledWith, threads);
        DrawStartingPixels(startingPoint, pointToExecuteAt + QPoint(0, -1), startingColor, colorToBeFilledWith, threads);
    }
}

void DrawingBoard::GenericFill(QPoint startingPoint, QPoint& pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith)
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
    update();
}

void DrawingBoard::paintEvent(QPaintEvent* event)
{
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
