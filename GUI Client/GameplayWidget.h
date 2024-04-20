#pragma once

#include <Qt6/QtWidgets/QWidget>
#include <Qt6/QtWidgets/QLabel>
#include <Qt6/QtWidgets/QListWidget>
#include <Qt6/QtWidgets/QBoxLayout>
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

	void NotifyEndGame(bool leavedGame);
	void SetGameSettings(std::tuple<int, int, int> gameSettings) noexcept;
	void ResetGameStatus();
	void Clear() noexcept;

public slots:
	void showEvent(QShowEvent* event) override;

	void OnEraserButtonReleased() noexcept;
	void OnUndoButtonReleased() noexcept;
	void OnFillButtonReleased() noexcept;
	void OnCanvasCleared()  noexcept;
	void OnPencilButtonReleased() noexcept;

private:
	void CheckTime(std::atomic<bool>& stop);
	void CheckForGameStatus();
	void CheckForUpdatesInGameScene(std::atomic<bool>& stop);
	void CheckForLessNecessaryUpdates(std::atomic<bool>& stop);
	void AddWordOption(const std::string& word);

	void ShowDrawerInterface();
	void ShowGuesserInterface();

	void HideBackgroundForGuesserWhenDrawingStarts();
	void HideBackgroundForDrawerWhenDrawingStarts();

	void GetCurrentPlayers();
	void PickingWordActions();

private:

private:
	const std::string kPickingWord = "PickingWord";
	const std::string kDrawing = "Drawing";
	const std::string kFinished = "Finished";

	std::string m_gameStatus;
	
	QString m_drawerName;
	//QTimer m_timer;

	std::atomic<bool> m_stop;
	int m_drawTime					 {};
	int m_rounds					 {};
	int m_wordsCount				 {};

	bool m_firstShow				 { true };
	bool m_isDrawer					 { false };
	QLabel* m_waitingTextLabel		 { new QLabel() };
	QLabel* m_wordToDraw			 { new QLabel{} };
	QLabel* m_timerLabel				 { new QLabel{} };
	QLabel* m_roundsLabel				 { new QLabel{} };
	DrawingBoard* m_drawingBoard		 { new DrawingBoard{} };
	ToolsFrame* m_toolsFrame			 { new ToolsFrame{} };
	Chat* m_chat						 { new Chat{} };
	ScoreboardTable* m_scoreboardTable { new ScoreboardTable{} };

	bool m_isEraserEnabled			 { false };
	QCursor m_eraserCursor			 { QCursor(QPixmap(":/image/eraser_cursor").scaled(25, 25)) };
	QCursor m_fillCursor				 { QCursor(QPixmap(":/image/fill_cursor").scaled(25, 25)) };
	QCursor m_pencilCursor			 { Qt::CrossCursor };

	QWidget* m_backgroundForDrawer					{ new QWidget{} };
	QWidget* m_backgroundForGuesser					{ new QWidget{} };
	QHBoxLayout* m_wordsToChooseLayout				{ new QHBoxLayout{} };
	QHBoxLayout* m_waitingForWordToBepickedLayout		{ new QHBoxLayout{} };
	std::vector<QPushButton*> m_wordsToChoose			{};
};
