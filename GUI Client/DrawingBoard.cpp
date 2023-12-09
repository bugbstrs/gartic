#include "DrawingBoard.h"
#include <thread>
#include <future>

DrawingBoard::DrawingBoard(QWidget* parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    ChangePenPropertiesTo(Qt::black, 2);
    undo = false;
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
    pen.setColor(Qt::white);
}

void DrawingBoard::ToggleFill(bool value)
{
    fillEnabled = value;
}

void DrawingBoard::EnablePencil()
{
    pen.setColor(pen.color());
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
    /*bool topDone = false;
    bool bottomDone = false;
    bool leftDone = false;
    bool rightDone = false;*/
    /*image.setPixelColor(startingPoint, colorToBeFilledWith);*/
    QPoint currentPointTop = pointToExecuteAt + QPoint(0, 1);
    QPoint currentPointBottom = pointToExecuteAt + QPoint(0, -1);
    QPoint currentPointLeft = pointToExecuteAt + QPoint(-1, 0);
    QPoint currentPointRight = pointToExecuteAt + QPoint(1, 0);

    std::thread topFill = std::thread(&DrawingBoard::GenericFill, this, currentPointTop, std::ref(currentPointTop), startingColor, colorToBeFilledWith, std::ref(availableDirections["topDone"]));

    std::thread bottomFill = std::thread(&DrawingBoard::GenericFill, this, currentPointBottom, std::ref(currentPointBottom), startingColor, colorToBeFilledWith, std::ref(availableDirections["bottomDone"]));

    std::thread leftFill = std::thread(&DrawingBoard::GenericFill, this, currentPointLeft, std::ref(currentPointLeft), startingColor, colorToBeFilledWith, std::ref(availableDirections["leftDone"]));

    std::thread rightFill = std::thread(&DrawingBoard::GenericFill, this, currentPointRight, std::ref(currentPointRight), startingColor, colorToBeFilledWith, std::ref(availableDirections["rightDone"]));

    /*std::thread topFill = std::thread(&DrawingBoard::FillTop, this, startingPoint + QPoint(0, 1), pointToExecuteAt + QPoint(0, 1), std::ref(currentPointTop), startingColor, colorToBeFilledWith);

    std::thread bottomFill = std::thread(&DrawingBoard::FillBottom, this, startingPoint + QPoint(0, -1), pointToExecuteAt + QPoint(0, -1), std::ref(currentPointBottom), startingColor, colorToBeFilledWith);

    std::thread leftFill = std::thread(&DrawingBoard::FillLeft, this, startingPoint + QPoint(-1, 0), pointToExecuteAt + QPoint(-1, 0), std::ref(currentPointLeft), startingColor, colorToBeFilledWith);

    std::thread rightFill = std::thread(&DrawingBoard::FillRight, this, startingPoint + QPoint( 1, 0), pointToExecuteAt + QPoint(1, 0), std::ref(currentPointRight),  startingColor, colorToBeFilledWith);*/

    //while (true) {
    //    if (topFill.joinable() && !availableDirections["topDone"]) {
    //        availableDirections["topDone"] = true;
    //        topFill.join();
    //        std::thread newThread1(&DrawingBoard::FillBottom, this, currentPointBottom, currentPointBottom, std::ref(currentPointBottom), startingColor, colorToBeFilledWith);
    //        if (newThread1.joinable())
    //            newThread1.join();
    //        //newThread1.detach();
    //    }
    //    if (bottomFill.joinable() && !availableDirections["bottomDone"]) {
    //        availableDirections["bottomDone"] = true;
    //        bottomFill.join();
    //        std::thread newThread2(&DrawingBoard::FillTop, this, currentPointTop, currentPointTop, std::ref(currentPointTop), startingColor, colorToBeFilledWith);
    //        if (newThread2.joinable())
    //            newThread2.join();
    //        //newThread2.detach();
    //    }
    //    if (leftFill.joinable() && !availableDirections["leftDone"]) {
    //        availableDirections["leftDone"] = true;
    //        leftFill.join();
    //        std::thread newThread3(&DrawingBoard::FillRight, this, currentPointRight, currentPointRight, std::ref(currentPointRight), startingColor, colorToBeFilledWith);
    //        if (newThread3.joinable())
    //            newThread3.join();
    //        //newThread3.detach();
    //    }
    //    if (rightFill.joinable() && !availableDirections["rightDone"]) {
    //        availableDirections["rightDone"] = true;
    //        rightFill.join();
    //        std::thread newThread4(&DrawingBoard::FillLeft, this, currentPointLeft, currentPointLeft, std::ref(currentPointLeft), startingColor, colorToBeFilledWith);
    //        if (newThread4.joinable())
    //            newThread4.join();
    //        //newThread4.detach();
    //    }
    //    if (!topFill.joinable() && !bottomFill.joinable() && !leftFill.joinable() && !rightFill.joinable())
    //        break;
    //}
    //topFill.join();
    //bottomFill.join();
    //leftFill.join();
    //rightFill.join();

    auto getAvailableDirection = [this, &currentPointTop, &currentPointBottom, &currentPointLeft, &currentPointRight]() -> QPoint& {
        if (availableDirections["topDone"])
            return currentPointTop;
        if (availableDirections["bottomDone"])
            return currentPointBottom;
        if (availableDirections["leftDone"])
            return currentPointLeft;
        if (availableDirections["rightDone"])
            return currentPointRight;
    };
    //De modifcat bool urile cu .joinable() in lambda
    while (true) {
        if (!topFill.joinable() && !bottomFill.joinable() && !leftFill.joinable() && !rightFill.joinable())
            break;
        /*QPoint& pixelToStartFilling = getAvailableDirection();*/
        if (availableDirections["topDone"] && topFill.joinable()) {
            availableDirections["topDone"] = false;
            topFill = std::thread(&DrawingBoard::GenericFill, this, currentPointBottom, std::ref(currentPointBottom), startingColor, colorToBeFilledWith, std::ref(availableDirections["topDone"]));
        }

        if (availableDirections["bottomDone"] && bottomFill.joinable()) {
            availableDirections["bottomDone"] = false;
            bottomFill = std::thread(&DrawingBoard::GenericFill, this, currentPointTop, std::ref(currentPointTop), startingColor, colorToBeFilledWith, std::ref(availableDirections["bottomDone"]));
        }

        if (availableDirections["leftDone"] && leftFill.joinable()) {
            availableDirections["leftDone"] = false;
            leftFill = std::thread(&DrawingBoard::GenericFill, this, currentPointRight, std::ref(currentPointRight), startingColor, colorToBeFilledWith, std::ref(availableDirections["leftDone"]));
        }

        if (availableDirections["rightDone"] && rightFill.joinable()) {
            availableDirections["rightDone"] = false;
            rightFill = std::thread(&DrawingBoard::GenericFill, this, currentPointLeft, std::ref(currentPointLeft), startingColor, colorToBeFilledWith, std::ref(availableDirections["rightDone"]));
        }
        topFill.join();
        bottomFill.join();
        leftFill.join();
        rightFill.join();
    }
    availableDirections = {
        {"topDone", false},
        {"bottomDone", false},
        {"leftDone", false},
        {"rightDone", false}
    };
}

void DrawingBoard::GenericFill(QPoint startingPoint, QPoint& pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith, bool& done)
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
        pointsQueue.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        pointsQueue.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
        pointsQueue.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
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
