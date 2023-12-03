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
	drawingBoard->changePenColor(color);
}

void GameplayWidget::ChangePenWidth(int width)
{
	drawingBoard->changePenWidth(width);
}

void GameplayWidget::showEvent(QShowEvent* event) {
	wordToDraw = findChild<QLabel*>("wordToGuessLabel");
	drawingBoard = findChild<DrawingBoard*>("drawingBoardCanvas");
	toolsFrame = findChild<ToolsFrame*>("toolsFrame");
	chat = findChild<Chat*>("chatFrame");

	QObject::connect(toolsFrame, &ToolsFrame::ColorChanged, this, &GameplayWidget::ChangePenColor);
	QObject::connect(toolsFrame, &ToolsFrame::WidthChanged, this, &GameplayWidget::ChangePenWidth);

	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/fetchword" });
	auto word = crow::json::load(response.text);
	std::string firstWord = std::string(word[0]["word"]);
	QString newWord = QString::fromUtf8(firstWord);
	wordToDraw->setText(newWord);
	chat->SetWordToGuess(newWord);
}
