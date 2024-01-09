#include "GameplayWidget.h"
#include <qthread.h>
#include <QPropertyAnimation>
#include "UserCredentials.h"

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

void GameplayWidget::Clear() noexcept
{
	isEraserEnabled = false;
	wordToDraw->clear();
	scoreboardTable->ClearScoreboard();
	drawingBoard->setCursor(pencilCursor);
	drawingBoard->ResetBoard();
	toolsFrame->ResetCurrentColorView();
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

void GameplayWidget::ShowWordDependingOnPlayerType(const QString& word) noexcept
{
	if (!m_isDrawer) {
		QString hiddenWord;
		for (int index = 0; index < word.size(); index++)
			hiddenWord += "_ ";
		wordToDraw->setText(hiddenWord);
		toolsFrame->hide();
		
		chat->SetWordToGuess(word);
	}
	else {
		wordToDraw->setText(word);
		toolsFrame->show();
		drawingBoard->setDisabled(false);
	}
	chat->SetChatConfigurationAccordingToPlayerType(m_isDrawer);
}

void GameplayWidget::BackgroundChangeForGuessersOnDrawerPickingWord()
{
	drawingBoard->setDisabled(true);
	backgroundForGuesser->hide();
}

void GameplayWidget::AddPlayers()
{
	scoreboardTable->model()->sort(1, Qt::DescendingOrder);
}

void GameplayWidget::AddWordOption(const std::string& word)
{
	QPushButton* wordButton = new QPushButton(QString::fromUtf8(word));
	wordButton->setMaximumSize(100, 50);
	wordButton->setCursor(Qt::PointingHandCursor);
	wordButton->setStyleSheet(
		"QPushButton {"
		"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"                                stop: 0 #4CAF50, stop: 1 #2196F3);"
		"    color: white;"
		"    border: 2px solid #4CAF50;"
		"    border-radius: 20px;"
		"    padding: 5px 10px;"
		"    font-family: \"Consolas\";"
		"    font-size: 20px;"
		"    font-weight: bold;"
		"}"

		"QPushButton:checked {"
		"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"                                stop: 0 #FFD700, stop: 1 #FFA500);"
		"    border: 2px solid #FFD700;"
		"    color: black;"
		"}"

		"QPushButton:hover {"
		"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"                                stop: 0 #6B6B6B, stop: 1 #8B8B8B);"
		"    border: 2px solid #808080;"
		"    color: white;"
		"}"
	);
	wordsToChoose.push_back(wordButton);
	wordsToChooseLayout->addWidget(wordButton);
	QObject::connect(wordButton, &QPushButton::released, [this, wordButton]() { 
		auto wordToGuessPosted = cpr::Post(
			cpr::Url{ "http://localhost:18080/putwordtoguess" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()},
				{"word", wordButton->text().toUtf8().constData()}
			}
		);
		if (wordToGuessPosted.status_code == 200) {
			ShowWordDependingOnPlayerType(wordButton->text());
			for (auto& button : wordsToChoose) {
				button->hide();
			}
			backgroundForDrawer->hide();
			drawingBoard->SetIsChoosingWord(false);
		}
	});

}

void GameplayWidget::showEvent(QShowEvent* event) {

	if (firstShow) {
		wordToDraw = findChild<QLabel*>("wordToGuessLabel");
		timerLabel = findChild<QLabel*>("timerLabel");
		roundsLabel = findChild<QLabel*>("roundsLabel");
		drawingBoard = findChild<DrawingBoard*>("drawingBoardCanvas");
		toolsFrame = findChild<ToolsFrame*>("toolsFrame");
		chat = findChild<Chat*>("chatFrame");
		scoreboardTable = findChild<ScoreboardTable*>("scoreboardTable");
		backgroundForDrawer = new QWidget(drawingBoard);
		backgroundForGuesser = new QWidget(drawingBoard);
		wordsToChooseLayout = new QHBoxLayout(backgroundForDrawer);
		waitingForWordToBepickedLayout = new QHBoxLayout(backgroundForGuesser);

		QObject::connect(toolsFrame, &ToolsFrame::OnColorChangedSignal, this, &GameplayWidget::ChangePenColor);
		QObject::connect(toolsFrame, &ToolsFrame::OnWidthChangedSignal, this, &GameplayWidget::ChangePenWidth);
		QObject::connect(toolsFrame, &ToolsFrame::OnEraserButtonReleasedSignal, this, &GameplayWidget::OnEraserButtonReleased);
		QObject::connect(toolsFrame, &ToolsFrame::OnUndoButtonReleasedSignal, this, &GameplayWidget::OnUndoButtonReleased);
		QObject::connect(toolsFrame, &ToolsFrame::OnFillButtonReleasedSignal, this, &GameplayWidget::OnFillButtonReleased);
		QObject::connect(toolsFrame, &ToolsFrame::OnCanvasClearedSignal, this, &GameplayWidget::OnCanvasCleared);
		QObject::connect(toolsFrame, &ToolsFrame::OnPencilButtonReleasedSignal, this, &GameplayWidget::OnPencilButtonReleased);

		timerLabel->setText(QString::number(drawTime));
		roundsLabel->setText(QString("Round 1 of ") + QString::number(rounds));
		backgroundForDrawer->setGeometry(0, 0, drawingBoard->width(), drawingBoard->height()); 
		backgroundForGuesser->setGeometry(0, 0, drawingBoard->width(), drawingBoard->height());

		firstShow = false;
	}

	AddPlayers();

	if (m_isDrawer) {
		drawingBoard->SetIsChoosingWord(true);
		backgroundForDrawer->setStyleSheet(
			"background-image: url(:/settings/WordsBackground);"
			"background-position: center;"
			"background-repeat: no-repeat;"
		);
		cpr::Response response = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchnwords" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		auto words = crow::json::load(response.text);
		for (int index = 0; index < words["words"].size(); index++) {
			AddWordOption(std::string(words["words"][index]));
		}
		backgroundForDrawer->show();
	}
	else {
		QLabel* waitingTextLabel { new QLabel()};
		waitingTextLabel->setStyleSheet("QLabel {"
			"  text-align: center;"
			"  font-size: 24px;"
			"  font-family: Consolas, monospace;"
			"}");
		waitingTextLabel->setText(QString("Waiting for ") + QString(scoreboardTable->itemAt(0, 0)->text()) + QString(" to choose a word..."));
		drawingBoard->SetIsChoosingWord(true);
		backgroundForGuesser->setStyleSheet(
			"background-color: grey;"
		);
		waitingForWordToBepickedLayout->addWidget(waitingTextLabel);
		waitingForWordToBepickedLayout->setAlignment(Qt::AlignCenter);
		backgroundForGuesser->setLayout(waitingForWordToBepickedLayout);
		backgroundForGuesser->show();
		ShowWordDependingOnPlayerType("Cuvant");
	}
}
