#include "GameplayWidget.h"

GameplayWidget::GameplayWidget(QWidget *parent)
	: QWidget(parent),
	wordToDraw(new QLabel())
{}

GameplayWidget::~GameplayWidget()
{}

void GameplayWidget::showEvent(QShowEvent* event) {
	wordToDraw = findChild<QLabel*>("wordToGuessLabel");
	/*cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/products" });
	auto word = crow::json::load(response.text);
	int index = 0;
	std::string firstWord = std::string(word[0]["word"]);
	QString newWord = QString::fromUtf8(firstWord);
	wordToDraw->setText(newWord);*/
}
