#include "GameplayWidget.h"

GameplayWidget::GameplayWidget(QWidget *parent)
	: QWidget(parent),
	wordToDraw(new QLabel())
{}

GameplayWidget::~GameplayWidget()
{}

void GameplayWidget::showEvent(QShowEvent* event) {
	wordToDraw = findChild<QLabel*>("wordToGuessLabel");/*
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/products" });*/
	/*std::string fetchedWord = std::string(crow::json::load(response.text));
	wordToDraw->setText(QString::fromStdString(fetchedWord));*/
}
