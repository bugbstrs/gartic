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
#include "crow.h"

class GameplayWidget  : public QWidget
{
	Q_OBJECT

public:
	GameplayWidget(QWidget *parent);
	~GameplayWidget();

	void ChangePenColor(QColor color);
	void ChangePenWidth(int width);

public slots:
	void showEvent(QShowEvent* event);
	void OnEraserButtonReleased();
	void OnUndoButtonReleased();
	void OnFillButtonReleased();
	void OnCanvasCleared();
	void OnPencilButtonReleased();

private:
	struct Player {
		std::string name;
		int points;
	};
private:
	void AddPlayers();

private:
	QLabel* wordToDraw;
	DrawingBoard* drawingBoard;
	ToolsFrame* toolsFrame;
	Chat* chat;
	ScoreboardTable* scoreboardTable;
};
