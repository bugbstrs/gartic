#include "DrawingBoard.h"
#include "UserCredentials.h"
#include <sstream>
#include "crow.h"

DrawingBoard::DrawingBoard(QWidget* parent)
	: QWidget{ parent },
	m_eraserColor{ Qt::white },
	m_stop(false)
{
	setMouseTracking(true);
	ChangePenPropertiesTo(Qt::black, 4);
}

void DrawingBoard::mousePressEvent(QMouseEvent* event)
{
	if (m_isChoosingWord)
		return;
	images.push_back(image);
	if (event->button() == Qt::LeftButton) {
		if (!m_fillEnabled) {
			m_drawing = true;
			m_currentPath = QPainterPath(event->pos());
			m_pathPoints.push_back({ event->pos(), true });
			m_drawBeginningOfPath = false;
			update();

		}
		else {
			QPoint mouseRegisteredPosition = event->pos() + QPoint(-12, 10);
			FloodFill(mouseRegisteredPosition, mouseRegisteredPosition, image.pixelColor(mouseRegisteredPosition), m_pen.color());

			std::string drawEvent = "fill ";
			drawEvent += std::to_string(mouseRegisteredPosition.x()) + " ";
			drawEvent += std::to_string(mouseRegisteredPosition.y()) + " ";
			QColor color = m_pen.color();

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
	if (m_drawing) {
		m_currentPath.lineTo(event->pos());
		m_pathPoints.push_back({ event->pos(), false });
		update();
	}
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_drawing) {
		m_drawing = false;
		m_drawBeginningOfPath = false;
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
	m_lastColor = color;
	m_pen.setColor(color);
	m_pen.setWidth(width);
	m_pen.setCapStyle(Qt::RoundCap);
}

void DrawingBoard::ChangePenColor(QColor color) noexcept
{
	m_lastColor = color;
	m_pen.setColor(color);
}

void DrawingBoard::ChangePenWidth(int width) noexcept
{
	m_pen.setWidth(width);
}

void DrawingBoard::SetIsChoosingWord(bool value) noexcept
{
	m_isChoosingWord = value;
}

void DrawingBoard::SetupForDrawer(bool isDrawer) noexcept
{
	m_stop.store(isDrawer);

	std::thread sendUpdatedPath(&DrawingBoard::SendUpdatedPath, this, std::ref(m_stop));
	std::thread checkForNewDrawEvents(&DrawingBoard::CheckForNewDrawEvents, this, std::ref(m_stop));

	sendUpdatedPath.detach();
	checkForNewDrawEvents.detach();

}

void DrawingBoard::ToggleEraser(bool value) noexcept
{
	if (value)
		m_pen.setColor(m_eraserColor);
	else m_pen.setColor(m_lastColor);
}

void DrawingBoard::ToggleFill(bool value) noexcept
{
	m_fillEnabled = value;
}

void DrawingBoard::EnablePencil() noexcept
{
	m_pen.setColor(m_lastColor);
}

void DrawingBoard::UndoLastPath() noexcept
{
	UndoAction();

	std::string drawEvent = "undo";

	std::vector<crow::json::wvalue> drawEventsJSON;
	drawEventsJSON.push_back(drawEvent);
	crow::json::wvalue drawEventsParameter = drawEventsJSON;

	bool eventSent = false;
	while (!eventSent) {
		auto sentUndoCoordinates = cpr::Post(
			cpr::Url{ "http://localhost:18080/putdraweventsindrawingboard" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()},
				{"events", drawEventsParameter.dump()}
			}
		);
		if (sentUndoCoordinates.status_code == 200)
			eventSent = true;
	}

}

void DrawingBoard::StopLookingForUpdates() noexcept
{
	m_stop.store(!m_stop.load());
}

void DrawingBoard::ClearCanvas() noexcept
{
	ClearAction();

	std::string drawEvent = "clear";

	std::vector<crow::json::wvalue> drawEventsJSON;
	drawEventsJSON.push_back(drawEvent);
	crow::json::wvalue drawEventsParameter = drawEventsJSON;

	bool eventSent = false;
	while (!eventSent) {
		auto sentClearCoordinates = cpr::Post(
			cpr::Url{ "http://localhost:18080/putdraweventsindrawingboard" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()},
				{"events", drawEventsParameter.dump()}
			}
		);
		if (sentClearCoordinates.status_code == 200)
			eventSent = true;
	}

}

void DrawingBoard::ResetBoard() noexcept
{
	m_isChoosingWord = false;
	m_drawing = false;
	m_fillEnabled = false;
	m_drawBeginningOfPath = false;

	ChangePenPropertiesTo(kDefaultPenColor, kDefaultPenWidth);
	m_currentPath = QPainterPath();
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
	QMetaObject::invokeMethod(this, [this]() {
		m_pathPoints.clear();
		m_currentPath = QPainterPath();
		image.fill(Qt::white);
		images.clear();
		update();
	}, Qt::QueuedConnection);
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
		if (fetchedDrawingEvents.status_code == 200) {
			auto events = crow::json::load(fetchedDrawingEvents.text);
			for (int index{ 0 }; index < events["events"].size(); ++index) {
				RunEventTypeAccordingly(std::string(events["events"][index]));
				if (index % 100 == 0)
					update();
			}
		}
		update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	if (stop.load()) {

	}
}

void DrawingBoard::SendUpdatedPath(std::atomic<bool>& stop)
{
	std::string drawEvent;
	std::deque <std::pair<QPoint, bool>> pathPoints;
	std::vector<crow::json::wvalue> drawEventsJSON;
	while (stop.load()) {
		{
			std::lock_guard<std::mutex> lock(m_mtx);
			pathPoints = m_pathPoints;
			while (!m_pathPoints.empty()) {
				m_pathPoints.pop_front();
			}
		}
		while (!pathPoints.empty()) {
			if (pathPoints.front().second) {
				drawEvent = "startDrawing ";
				drawEvent += std::to_string(pathPoints.front().first.x()) + " ";
				drawEvent += std::to_string(pathPoints.front().first.y()) + " ";
				QColor color = m_pen.color();
				int red = color.red();
				int green = color.green();
				int blue = color.blue();
				int colorAsInt = (red << 16) | (green << 8) | blue;
				drawEvent += std::to_string(colorAsInt) + " ";
				drawEvent += std::to_string(m_pen.width());

				drawEventsJSON.push_back(drawEvent);
				drawEvent.clear();
				pathPoints.pop_front();
			}
			else {
				drawEvent = "keepDrawing ";
				drawEvent += std::to_string(pathPoints.front().first.x()) + " ";
				drawEvent += std::to_string(pathPoints.front().first.y());

				drawEventsJSON.push_back(drawEvent);
				drawEvent.clear();
				pathPoints.pop_front();
			}
		}
		if (!drawEventsJSON.empty()) {
			crow::json::wvalue drawEventsParameter = drawEventsJSON;
			bool drawingSent = false;
			while (!drawingSent) {
				auto sentFillCoordinatesResponse = cpr::Post(
					cpr::Url{ "http://localhost:18080/putdraweventsindrawingboard" },
					cpr::Parameters{
						{"password", UserCredentials::GetPassword()},
						{"username", UserCredentials::GetUsername()},
						{"events", drawEventsParameter.dump()}
					}
				);
				if (sentFillCoordinatesResponse.status_code == 200)
					drawingSent = true;
			}
			drawEventsJSON.clear();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
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
			images.push_back(image);
			int color, width;
			drawEventStream >> prevX >> prevY >> color >> width;
			m_drawing = true;
			int red = (color >> 16) & 0xFF;
			int green = (color >> 8) & 0xFF;
			int blue = color & 0xFF;

			m_pen.setColor(QColor(red, green, blue));
			m_pen.setWidth(width);
			m_currentPath = QPainterPath(QPoint(prevX, prevY));
		}
		else if (string == "keepDrawing")
		{
			int x, y;
			drawEventStream >> x >> y;
			m_currentPath.lineTo(QPoint(x, y));
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
			m_currentPath.clear();
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
	if (m_firstPaint) {
		setAutoFillBackground(true);
		m_firstPaint = false;
	}
	else {
		QPainter imagePainter(this);
		imagePainter.drawImage(0, 0, image);
		QPainter painter(&image);

		if (m_drawing) {
			painter.setPen(m_pen);
			if (m_currentPath.elementCount() == 1)
				painter.drawPoint(m_currentPath.elementAt(0));
			else painter.drawPath(m_currentPath);
		}
	}
}
