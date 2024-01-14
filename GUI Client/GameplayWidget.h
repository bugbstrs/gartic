#pragma once

#include <QWidget>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include "DrawingBoard.h"
#include "ToolsFrame.h"
#include "Chat.h"
#include "ScoreboardTable.h"
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <cpr/cpr.h>
#include <atomic>

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

	void SetGameSettings(std::tuple<int, int, int> gameSettings);
	//void SetIsDrawer(bool isDrawer);
	
	void Clear() noexcept;

public slots:
	void showEvent(QShowEvent* event) override;

	void OnEraserButtonReleased() noexcept;
	void OnUndoButtonReleased() noexcept;
	void OnFillButtonReleased() noexcept;
	void OnCanvasCleared()  noexcept;
	void OnPencilButtonReleased() noexcept;

signals:
	void OnGameFinished();

private:
	void CheckTime(std::atomic<bool>& stop);
	void CheckForUpdatesInGameScene(std::atomic<bool>& stop);
	void CheckForLessNecessaryUpdates(std::atomic<bool>& stop);
	void AddPlayers();
	void AddWordOption(const std::string& word);

	void ShowDrawerInterface();
	void ShowGuesserInterface();

	void BackgroundChangeForGuessersOnDrawerPickingWord();
	void BackgroundChangeForDrawer();

private:
	struct Player {
		std::string name;
		int points;
	};
	enum class GameStatus
	{
		PickingWord,
		Drawing,
		Finished
	};

private:
	const std::string kPickingWord = "PickingWord";
	const std::string kDrawing = "Drawing";
	const std::string kFinished = "Finished";
	std::atomic<bool> stop;
	int m_drawTime					 {};
	int m_rounds					 {};
	int m_wordsCount				 {};

	bool firstShow					 { true };
	bool m_isDrawer					 { true };
	QLabel* wordToDraw				 { new QLabel{} };
	QLabel* timerLabel				 { new QLabel{} };
	QLabel* roundsLabel				 { new QLabel{} };
	DrawingBoard* drawingBoard		 { new DrawingBoard{} };
	ToolsFrame* toolsFrame			 { new ToolsFrame{} };
	Chat* chat						 { new Chat{} };
	ScoreboardTable* scoreboardTable { new ScoreboardTable{} };

	bool isEraserEnabled			 { false };
	QCursor eraserCursor			 { QCursor(QPixmap(":/image/eraser_cursor").scaled(25, 25)) };
	QCursor fillCursor				 { QCursor(QPixmap(":/image/fill_cursor").scaled(25, 25)) };
	QCursor pencilCursor			 { Qt::CrossCursor };

	QWidget* backgroundForDrawer					{ new QWidget{} };
	QWidget* backgroundForGuesser					{ new QWidget{} };
	QHBoxLayout* wordsToChooseLayout				{ new QHBoxLayout{} };
	QHBoxLayout* waitingForWordToBepickedLayout		{ new QHBoxLayout{} };
	std::vector<QPushButton*> wordsToChoose			{};
};
