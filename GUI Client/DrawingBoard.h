#pragma once

#include <QWidget>
#include <qimage.h>
#include <QMouseEvent>
#include <qpainter.h>
#include <qpainterpath.h>
#include <queue>
#include <atomic>
#include <stack>
#include <thread>

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

	void SetIsChoosingWord(bool value);

	void ToggleEraser(bool value) noexcept;
	void ToggleFill(bool value) noexcept;
	void EnablePencil() noexcept;
	void UndoLastPath() noexcept;
	void ClearCanvas() noexcept;

	void ResetBoard() noexcept;

protected:
	void showEvent(QShowEvent* event) override;

	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

private:
	void CheckForNewDrawEvents(std::atomic<bool>& stop);

	void FloodFill(QPoint startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);
	void GenericFill(QPoint startingPoint, QPoint& pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith);
	void DrawStartingPixels(const QPoint& startingPoint, QPoint pointToExecuteAt, QColor startingColor, QColor colorToBeFilledWith, std::vector <std::thread>& threads);

private:
	const QColor kDefaultPenColor{ Qt::black };
	const int kDefaultPenWidth { 4 };
	const int kCircleRadius { 25 };
	std::atomic<bool>stop;

	bool isChoosingWord		{ false };
	bool firstPaint			{ true };
	bool drawing			{ false };
	bool fillEnabled		{ false };

	QColor lastColor	{};
	QColor eraserColor	{};

	QPen pen										 {};
	QPainterPath currentPath						 {};
	std::vector<std::pair<QPainterPath, QPen>> paths {};

	std::vector<QImage>images								  {};
	QImage image											  {};
};
