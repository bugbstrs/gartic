#pragma once

#include <QWidget>
#include <qlabel.h>
#include "DrawingBoard.h"
#include "ToolsFrame.h"
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

public slots:
	void showEvent(QShowEvent* event);


private:
	QLabel* wordToDraw;
	DrawingBoard* drawingBoard;
	ToolsFrame* toolsFrame;
};
