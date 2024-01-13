#include "DrawingBoard.h"
#include "UserCredentials.h"
#include <sstream>
#include "crow.h"

DrawingBoard::DrawingBoard(QWidget* parent)
	: QWidget{ parent },
	eraserColor{ Qt::white },
	stop(false)
{
	setMouseTracking(true);
	ChangePenPropertiesTo(Qt::black, 4);

}

void DrawingBoard::mousePressEvent(QMouseEvent* event)
{
	if (isChoosingWord)
		return;
	images.push_back(image);
	if (event->button() == Qt::LeftButton) {
		if (!fillEnabled) {
			drawing = true;
			currentPath = QPainterPath(event->pos());
			//pathPoints.push(event->pos());
			pathPoints.push(event->pos());
			drawBeginningOfPath = false;
			update();

		}
		else {
			QPoint mouseRegisteredPosition = event->pos() + QPoint(-12, 10);
			FloodFill(mouseRegisteredPosition, mouseRegisteredPosition, image.pixelColor(mouseRegisteredPosition), pen.color());

			std::string drawEvent = "fill ";
			drawEvent += std::to_string(mouseRegisteredPosition.x()) + " ";
			drawEvent += std::to_string(mouseRegisteredPosition.y()) + " ";
			QColor color = pen.color();

			int red = color.red();
			int green = color.green();
			int blue = color.blue();

			int colorAsInt = (red << 16) | (green << 8) | blue;
			drawEvent += std::to_string(colorAsInt);

			std::vector<crow::json::wvalue> drawEventsJSON;
			drawEventsJSON.push_back(drawEvent);
			crow::json::wvalue drawEventsParameter = drawEventsJSON;

			auto sentFillCoordinatesResponse = cpr::Post(
				cpr::Url{ "http://localhost:18080/putdraweventsindrawingboard" },
				cpr::Parameters{
					{"password", UserCredentials::GetPassword()},
					{"username", UserCredentials::GetUsername()},
					{"events", drawEventsParameter.dump()}
				}
			);
		}
	}
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event)
{
	if (drawing) {
		currentPath.lineTo(event->pos());
		pathPoints.push(event->pos());
		update();
	}
}

//Isi da erase in timp ce parcurge ala
void DrawingBoard::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && drawing) {
		drawing = false;
		drawBeginningOfPath = false;
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

void DrawingBoard::SetupForDrawer(bool isDrawer)
{
	stop.store(isDrawer);

	//std::thread sendNewPathStared(&DrawingBoard::SendNewPathStared, this, std::ref(stop));
	std::thread sendUpdatedPath(&DrawingBoard::SendUpdatedPath, this, std::ref(stop));
	std::thread checkForNewDrawEvents(&DrawingBoard::CheckForNewDrawEvents, this, std::ref(stop));

	//sendNewPathStared.detach();
	sendUpdatedPath.detach();
	checkForNewDrawEvents.detach();


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
	UndoAction();

	std::string drawEvent = "undo";

	std::vector<crow::json::wvalue> drawEventsJSON;
	drawEventsJSON.push_back(drawEvent);
	crow::json::wvalue drawEventsParameter = drawEventsJSON;
	auto sentFillCoordinatesResponse = cpr::Post(
		cpr::Url{ "http://localhost:18080/putdraweventsindrawingboard" },
		cpr::Parameters{
			{"password", UserCredentials::GetPassword()},
			{"username", UserCredentials::GetUsername()},
			{"events", drawEventsParameter.dump()}
		}
	);

}

void DrawingBoard::ClearCanvas() noexcept
{
	ClearAction();

	std::string drawEvent = "clear";

	std::vector<crow::json::wvalue> drawEventsJSON;
	drawEventsJSON.push_back(drawEvent);
	crow::json::wvalue drawEventsParameter = drawEventsJSON;
	auto sentFillCoordinatesResponse = cpr::Post(
		cpr::Url{ "http://localhost:18080/putdraweventsindrawingboard" },
		cpr::Parameters{
			{"password", UserCredentials::GetPassword()},
			{"username", UserCredentials::GetUsername()},
			{"events", drawEventsParameter.dump()}
		}
	);

}

void DrawingBoard::ResetBoard() noexcept
{
	isChoosingWord = false;
	drawing = false;
	fillEnabled = false;
	lastColor = kDefaultPenColor;

	ChangePenPropertiesTo(kDefaultPenColor, kDefaultPenWidth);
	currentPath = QPainterPath();
	image.fill(Qt::white);
	images.clear();
}

void DrawingBoard::UndoAction()
{
	if (!images.empty()) {
		image = images.back();
		images.pop_back();
	}
	else image.fill(Qt::white);
	update();
}

void DrawingBoard::ClearAction()
{
	currentPath = QPainterPath();
	image.fill(Qt::white);
	images.clear();
	update();
}

void DrawingBoard::CheckForNewDrawEvents(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto fetchedDrawingEvents = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchdrawingboard" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		auto events = crow::json::load(fetchedDrawingEvents.text);
		for (int index = 0; index < events["events"].size(); index++) {
			RunEventTypeAccordingly(std::string(events["events"][index]));
			if (index % 150 == 0)
				update();
		}
		update();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	if (stop.load()) {

	}
}

void DrawingBoard::SendUpdatedPath(std::atomic<bool>& stop)
{
	std::string drawEvent;
	std::vector<crow::json::wvalue> drawEventsJSON;
	while (stop.load()) {
		if (!pathPoints.empty()) {
			if (drawBeginningOfPath == false) {
				drawEvent = "startDrawing ";
				drawEvent += std::to_string(pathPoints.front().x()) + " ";
				drawEvent += std::to_string(pathPoints.front().y()) + " ";
				QColor color = pen.color();
				int red = color.red();
				int green = color.green();
				int blue = color.blue();
				int colorAsInt = (red << 16) | (green << 8) | blue;
				drawEvent += std::to_string(colorAsInt) + " ";
				drawEvent += std::to_string(pen.width());

				drawEventsJSON.push_back(drawEvent);
				drawEvent.clear();
				pathPoints.pop();

				drawBeginningOfPath = true;
			}
			for (int index = 0; index < 200 && !pathPoints.empty(); ++index) {
				drawEvent = "keepDrawing ";
				drawEvent += std::to_string(pathPoints.front().x()) + " ";
				drawEvent += std::to_string(pathPoints.front().y()) + " ";

				drawEventsJSON.push_back(drawEvent);
				drawEvent.clear();
				pathPoints.pop();
			}
			crow::json::wvalue drawEventsParameter = drawEventsJSON;
			auto sentFillCoordinatesResponse = cpr::Post(
				cpr::Url{ "http://localhost:18080/putdraweventsindrawingboard" },
				cpr::Parameters{
					{"password", UserCredentials::GetPassword()},
					{"username", UserCredentials::GetUsername()},
					{"events", drawEventsParameter.dump()}
				}
			);
			drawEventsJSON.clear();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (!stop.load()) {

	}
}

void DrawingBoard::RunEventTypeAccordingly(const std::string& drawingEvent)
{
	QMetaObject::invokeMethod(this, [this, drawingEvent]() {
		std::istringstream drawEventStream{ drawingEvent };
		std::string string;
		drawEventStream >> string;
		static int prevX, prevY;
		if (string == "startDrawing")
		{
			if (!currentPath.isEmpty()) {
				update();
				images.push_back(image);
				currentPath.clear();
			}
			int color, width;
			drawEventStream >> prevX >> prevY >> color >> width;

			drawing = true;
			int red = (color >> 16) & 0xFF;
			int green = (color >> 8) & 0xFF;
			int blue = color & 0xFF;

			pen.setColor(QColor(red, green, blue));
			pen.setWidth(width);
			currentPath = QPainterPath(QPoint(prevX, prevY));
		}
		else if (string == "keepDrawing")
		{
			int x, y;
			drawEventStream >> x >> y;
			currentPath.lineTo(QPoint(x, y));
		}
		else if (string == "fill")
		{
			int x, y;
			int color;
			drawEventStream >> x >> y >> color;

			int red = (color >> 16) & 0xFF;
			int green = (color >> 8) & 0xFF;
			int blue = color & 0xFF;

			images.push_back(image);
			FloodFill(QPoint(x, y), QPoint(x, y), image.pixelColor(QPoint(x, y)), QColor(red, green, blue));
		}
		else if (string == "undo")
		{
			UndoAction();
		}
		else if (string == "clear")
		{
			ClearAction();
		}
	}, Qt::QueuedConnection);
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

void DrawingBoard::showEvent(QShowEvent* event)
{
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
			if (currentPath.elementCount() == 1)
				painter.drawPoint(currentPath.elementAt(0));
			else painter.drawPath(currentPath);
		}
	}
}
