#include "GameplayWidget.h"

GameplayWidget::GameplayWidget(QWidget *parent)
	: QWidget(parent),
	wordToDraw(new QLabel())
{
}

GameplayWidget::~GameplayWidget()
{}

void GameplayWidget::ChangePenColor(QColor color)
{
	drawingBoard->ChangePenColor(color);
}

void GameplayWidget::ChangePenWidth(int width)
{
	drawingBoard->ChangePenWidth(width);
}

void GameplayWidget::OnCanvasCleared()
{
	drawingBoard->ClearCanvas();
}

void GameplayWidget::OnEraserButtonReleased()
{
	drawingBoard->ToggleEraser();
}

void GameplayWidget::OnUndoButtonReleased()
{
	drawingBoard->UndoLastPath();
}

void GameplayWidget::OnFillButtonReleased()
{
	drawingBoard->Fill();
}

void GameplayWidget::showEvent(QShowEvent* event) {
	wordToDraw = findChild<QLabel*>("wordToGuessLabel");
	drawingBoard = findChild<DrawingBoard*>("drawingBoardCanvas");
	toolsFrame = findChild<ToolsFrame*>("toolsFrame");
	chat = findChild<Chat*>("chatFrame");

	QObject::connect(toolsFrame, &ToolsFrame::OnColorChangedSignal, this, &GameplayWidget::ChangePenColor);
	QObject::connect(toolsFrame, &ToolsFrame::OnWidthChangedSignal, this, &GameplayWidget::ChangePenWidth);
	QObject::connect(toolsFrame, &ToolsFrame::OnEraserButtonReleasedSignal, this, &GameplayWidget::OnEraserButtonReleased);
	QObject::connect(toolsFrame, &ToolsFrame::OnUndoButtonReleasedSignal, this, &GameplayWidget::OnUndoButtonReleased);
	QObject::connect(toolsFrame, &ToolsFrame::OnFillButtonReleasedSignal, this, &GameplayWidget::OnFillButtonReleased);
	QObject::connect(toolsFrame, &ToolsFrame::OnCanvasClearedSignal, this, &GameplayWidget::OnCanvasCleared);
	
	chat->SetWordToGuess(wordToDraw->text());

	/*cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/fetchword" });
	auto word = crow::json::load(response.text);
	std::string firstWord = std::string(word[0]["word"]);
	QString newWord = QString::fromUtf8(firstWord);
	wordToDraw->setText(newWord);
	chat->SetWordToGuess(newWord);*/
}
