#pragma once

#include <QWidget>
#include <qlabel.h>
#include <qlistwidget.h>
#include "DrawingBoard.h"
#include "ToolsFrame.h"
#include "Chat.h"
#include "ScoreboardTable.h"
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <cpr/cpr.h>

#pragma warning(push)

#pragma warning(disable: 4267)

#include "crow.h"

#pragma warning(pop)

class GameplayWidget  : public QWidget
{
	Q_OBJECT

public:
	GameplayWidget(QWidget *parent);
	~GameplayWidget();

	void ChangePenColor(QColor color) noexcept;
	void ChangePenWidth(int width) noexcept;

	void SetIconsAndNamesForPlayers();

public slots:
	void showEvent(QShowEvent* event) override;

	void OnEraserButtonReleased() noexcept;
	void OnUndoButtonReleased() noexcept;
	void OnFillButtonReleased() noexcept;
	void OnCanvasCleared()  noexcept;
	void OnPencilButtonReleased() noexcept;

private:
	void AddPlayers();
	void ShowWordDependingOnPlayerType() noexcept;

private:
	struct Player {
		std::string name;
		int points;
	};

private:
	bool isDrawer					 { true };
	QLabel* wordToDraw				 { new QLabel{} };
	DrawingBoard* drawingBoard		 { new DrawingBoard{} };
	ToolsFrame* toolsFrame			 { new ToolsFrame{} };
	Chat* chat						 { new Chat{} };
	ScoreboardTable* scoreboardTable { new ScoreboardTable{} };

	bool isEraserEnabled			 { false };
	QCursor eraserCursor			 { QCursor(QPixmap(":/image/eraser_cursor").scaled(25, 25)) };
	QCursor fillCursor				 { QCursor(QPixmap(":/image/fill").scaled(25, 25)) };
	QCursor pencilCursor			 { Qt::CrossCursor };
};
