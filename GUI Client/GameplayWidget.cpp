#include "GameplayWidget.h"
#include <qthread.h>

GameplayWidget::GameplayWidget(QWidget *parent)
	: QWidget{ parent }
{}

GameplayWidget::~GameplayWidget()
{}

void GameplayWidget::ChangePenColor(QColor color) noexcept
{
	if (isEraserEnabled) {
		drawingBoard->setCursor(pencilCursor);
		isEraserEnabled = false;
	}
	drawingBoard->ChangePenColor(color);
}

void GameplayWidget::ChangePenWidth(int width) noexcept
{
	drawingBoard->ChangePenWidth(width);
}

void GameplayWidget::SetGameSettings(std::tuple<int, int, int> gameSettings)
{
	drawTime = std::get<0>(gameSettings);
	rounds = std::get<1>(gameSettings);
	wordsCount = std::get<2>(gameSettings);
}

void GameplayWidget::OnCanvasCleared() noexcept
{
	drawingBoard->ClearCanvas();
}

void GameplayWidget::OnPencilButtonReleased() noexcept
{
	isEraserEnabled = false;
	drawingBoard->setCursor(pencilCursor);
	drawingBoard->ToggleEraser(false);
	drawingBoard->ToggleFill(false);
	drawingBoard->EnablePencil();
}

void GameplayWidget::OnEraserButtonReleased() noexcept
{
	isEraserEnabled = true;
	drawingBoard->setCursor(eraserCursor);
	drawingBoard->ToggleEraser(true);
	drawingBoard->ToggleFill(false);
}

void GameplayWidget::OnUndoButtonReleased() noexcept
{
	drawingBoard->UndoLastPath();
}

void GameplayWidget::OnFillButtonReleased() noexcept
{
	isEraserEnabled = false;
	drawingBoard->setCursor(fillCursor);
	drawingBoard->ToggleEraser(false);
	drawingBoard->ToggleFill(true);
}

void GameplayWidget::ShowWordDependingOnPlayerType() noexcept
{
	if (!isDrawer) {
		QString hiddenWord;
		for (int index = 0; index < wordToDraw->text().size(); index++)
			hiddenWord += "_ ";
		wordToDraw->setText(hiddenWord);
		toolsFrame->hide();
		drawingBoard->setDisabled(true);
	}
	else {
		toolsFrame->show();
		drawingBoard->setDisabled(false);
		chat->SetWordToGuess(wordToDraw->text());
	}
	chat->SetChatConfigurationAccordingToPlayerType(isDrawer);
}

void GameplayWidget::AddPlayers()
{
	scoreboardTable->model()->sort(1, Qt::DescendingOrder);
}

void GameplayWidget::showEvent(QShowEvent* event) {
	wordToDraw = findChild<QLabel*>("wordToGuessLabel");
	drawingBoard = findChild<DrawingBoard*>("drawingBoardCanvas");
	toolsFrame = findChild<ToolsFrame*>("toolsFrame");
	chat = findChild<Chat*>("chatFrame");
	scoreboardTable = findChild<ScoreboardTable*>("scoreboardTable");

	QObject::connect(toolsFrame, &ToolsFrame::OnColorChangedSignal, this, &GameplayWidget::ChangePenColor);
	QObject::connect(toolsFrame, &ToolsFrame::OnWidthChangedSignal, this, &GameplayWidget::ChangePenWidth);
	QObject::connect(toolsFrame, &ToolsFrame::OnEraserButtonReleasedSignal, this, &GameplayWidget::OnEraserButtonReleased);
	QObject::connect(toolsFrame, &ToolsFrame::OnUndoButtonReleasedSignal, this, &GameplayWidget::OnUndoButtonReleased);
	QObject::connect(toolsFrame, &ToolsFrame::OnFillButtonReleasedSignal, this, &GameplayWidget::OnFillButtonReleased);
	QObject::connect(toolsFrame, &ToolsFrame::OnCanvasClearedSignal, this, &GameplayWidget::OnCanvasCleared);
	QObject::connect(toolsFrame, &ToolsFrame::OnPencilButtonReleasedSignal, this, &GameplayWidget::OnPencilButtonReleased);
	
	chat->SetWordToGuess(wordToDraw->text());
	ShowWordDependingOnPlayerType();
	AddPlayers();

	/*cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/fetchword" });
	auto word = crow::json::load(response.text);
	std::string firstWord = std::string(word[0]["word"]);
	QString newWord = QString::fromUtf8(firstWord);
	wordToDraw->setText(newWord);
	chat->SetWordToGuess(newWord);*/
}
