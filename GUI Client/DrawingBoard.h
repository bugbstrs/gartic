#pragma once

#include <Qt6/QtWidgets/QWidget>
#include <Qt6/QtGui/QImage>
#include <Qt6/QtGui/QMouseEvent>
#include <Qt6/QtGui/QPainter>
#include <Qt6/QtGui/QPainterPath>
#include <deque>
#include <atomic>
#include <stack>
#include <thread>
#include <mutex>

class DrawingBoard : public QWidget
{
	Q_OBJECT

public:
	//Constructors
	DrawingBoard(QWidget* parent = nullptr);
	~DrawingBoard() = default;

	//Functionality
	void ChangePenPropertiesTo(QColor color, int width) noexcept;
	void ChangePenColor(QColor color) noexcept;
	void ChangePenWidth(int width) noexcept;

	void SetIsChoosingWord(bool value) noexcept;
	void SetupForDrawer(bool isDrawer) noexcept;

	void ToggleEraser(bool value) noexcept;
	void ToggleFill(bool value) noexcept;
	void EnablePencil() noexcept;
	void UndoLastPath() noexcept;
	void StopLookingForUpdates() noexcept;
	void ClearCanvas() noexcept;
	void ClearAction();

	void ResetBoard() noexcept;

protected:
	void showEvent(QShowEvent* event) override;

	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void UndoAction();

	void CheckForNewDrawEvents(std::atomic<bool>& stop);
	void SendUpdatedPath(std::atomic<bool>& stop);
	void RunEventTypeAccordingly(const std::string& drawingEvent);

	void FloodFill(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);
	void GenericFill(QPoint startingPoint, QPoint& pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);
	void DrawStartingPixels(const QPoint& startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith, std::vector <std::thread>& threads);

private:
	const QColor kDefaultPenColor						{ Qt::black };
	const int kDefaultPenWidth							{ 4 };
	const int kCircleRadius								{ 25 };
	std::atomic<bool>m_stop;

	std::deque<std::pair<QPoint, bool>> m_pathPoints	{};
	std::mutex m_mtx;
	
	bool m_isChoosingWord								{ false };
	bool m_firstPaint									{ true };
	bool m_drawing										{ false };
	bool m_fillEnabled									{ false };
	bool m_drawBeginningOfPath							{ false };

	QColor m_lastColor									{};
	QColor m_eraserColor								{};

	QPen m_pen											{};
	QPainterPath m_currentPath							{};

	std::vector<QImage>images			   				{};
	QImage image										{};
};
