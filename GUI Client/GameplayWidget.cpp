#include "GameplayWidget.h"
#include <qthread.h>
#include <QPropertyAnimation>
#include "UserCredentials.h"

GameplayWidget::GameplayWidget(QWidget *parent)
	: QWidget{ parent },
	stop(false)
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
	m_drawTime = std::get<0>(gameSettings);
	m_rounds = std::get<1>(gameSettings);
	m_wordsCount = std::get<2>(gameSettings);
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

void GameplayWidget::ShowDrawerInterface()
{
	QMetaObject::invokeMethod(this, [this]() {
		if (!backgroundForGuesser->isHidden())
			backgroundForGuesser->hide();
		drawingBoard->setDisabled(false);
		toolsFrame->show();
		backgroundForDrawer->show();
		drawingBoard->SetIsChoosingWord(true);
		drawingBoard->SetupForDrawer(true);
		chat->ToggleAccessToWritingMessages(false);
		cpr::Response response = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchwordstoguess" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		auto words = crow::json::load(response.text);
		for (int index = 0; index < words["words"].size(); index++) {
			AddWordOption(std::string(words["words"][index]));
		}
	}, Qt::QueuedConnection);
}

void GameplayWidget::ShowGuesserInterface()
{
	QMetaObject::invokeMethod(this, [this]() {
		if (!backgroundForDrawer->isHidden())
			backgroundForDrawer->hide();
		chat->ToggleAccessToWritingMessages(true);
		toolsFrame->hide();
		backgroundForGuesser->show();
		drawingBoard->SetIsChoosingWord(true);
		drawingBoard->SetupForDrawer(false);
	}, Qt::QueuedConnection);
}

void GameplayWidget::BackgroundChangeForGuessersOnDrawerPickingWord()
{
	QMetaObject::invokeMethod(this, [this]() {
		drawingBoard->SetIsChoosingWord(false);
		drawingBoard->setDisabled(true);
		backgroundForGuesser->hide();
	}, Qt::QueuedConnection);
}

void GameplayWidget::BackgroundChangeForDrawer()
{
	QMetaObject::invokeMethod(this, [this]() {
		for (QPushButton* button : wordsToChoose) {
			delete button;
		}
		wordsToChoose.clear();
		backgroundForDrawer->hide();
		drawingBoard->SetIsChoosingWord(false);
	}, Qt::QueuedConnection);
}

void GameplayWidget::CheckForUpdatesInGameScene(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto fetchedTime = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchtime" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		auto timeText = crow::json::load(fetchedTime.text);
		timerLabel->setText(QString::fromUtf8(std::string(timeText["time"])));

		auto response = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchplayers" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		auto playersResponse = crow::json::load(response.text);
		for (int index = 0; index < playersResponse["players"].size(); index++) {
			if (std::string(playersResponse["players"][index]["name"]) == UserCredentials::GetUsername()) {
				if (std::stoi(std::string(playersResponse["drawer index"])) == index) {
					m_isDrawer = true;
				}
				else {
					m_isDrawer = false;
				}
				chat->SetChatConfigurationAccordingToPlayerType(m_isDrawer);
				break;
			}
		}
		for (int index = 0; index < playersResponse["players"].size(); index++) {
			if (std::string(playersResponse["players"][index]["guessed"]) == "true") {
				scoreboardTable->MarkGuessedForPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])));
			}
			scoreboardTable->SetPointsToPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])), std::stoi(std::string(playersResponse["players"][index]["points"])));
		}

		auto fetchedGameStatus = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchgamestatus"},
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		if (fetchedGameStatus.status_code == 200) {
			auto gameStatusText = crow::json::load(fetchedGameStatus.text);
			if (std::string(gameStatusText["status"]) == kDrawing) {
				if (!m_isDrawer && !backgroundForGuesser->isHidden()) {
					BackgroundChangeForGuessersOnDrawerPickingWord();
				}
				if (m_isDrawer && !backgroundForDrawer->isHidden()) {
					BackgroundChangeForDrawer();
				}
				auto randomWordPicked = cpr::Get(
					cpr::Url{ "http://localhost:18080/fetchwordtodisplay" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()}
					}
				);
				auto pickedWord = crow::json::load(randomWordPicked.text);
				wordToDraw->setText(QString::fromUtf8(std::string(pickedWord["word"])));
			}
			if (std::string(gameStatusText["status"]) == kPickingWord) {
				wordToDraw->clear();
				if (m_isDrawer && backgroundForDrawer->isHidden())
					ShowDrawerInterface();
				if (!m_isDrawer && backgroundForGuesser->isHidden())
					ShowGuesserInterface();
			}
			if (std::string(gameStatusText["status"]) == kFinished) {
				auto response = cpr::Get(
					cpr::Url{ "http://localhost:18080/fetchplayers" },
					cpr::Parameters{
						{"password", UserCredentials::GetPassword()},
						{"username", UserCredentials::GetUsername()}
					}
				);
				stop.store(true);
				auto playersResponse = crow::json::load(response.text);
				for (int index = 0; index < playersResponse["players"].size(); index++) {
					scoreboardTable->SetPointsToPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])), std::stoi(std::string(playersResponse["players"][index]["points"])));
				}
				emit(OnGameFinished());
			}

		}

		auto fetchRoundNumber = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchroundnumber" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		
		auto roundText = crow::json::load(fetchRoundNumber.text);
		roundsLabel->setText(QString("Round %1").arg(QString::fromUtf8(std::string(roundText["round"]))));

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	if (stop.load()) {

	}
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
		bool accepted = false;

		while (!accepted)
		{
			auto wordToGuessPosted = cpr::Post(
				cpr::Url{ "http://localhost:18080/putwordtoguess" },
				cpr::Parameters{
					{"password", UserCredentials::GetPassword()},
					{"username", UserCredentials::GetUsername()},
					{"word", wordButton->text().toUtf8().constData()}
				}
			);

			if (wordToGuessPosted.status_code == 200)
			{
				accepted = true;
			}
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

		QLabel* waitingTextLabel{ new QLabel() };
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

		QObject::connect(toolsFrame, &ToolsFrame::OnColorChangedSignal, this, &GameplayWidget::ChangePenColor);
		QObject::connect(toolsFrame, &ToolsFrame::OnWidthChangedSignal, this, &GameplayWidget::ChangePenWidth);
		QObject::connect(toolsFrame, &ToolsFrame::OnEraserButtonReleasedSignal, this, &GameplayWidget::OnEraserButtonReleased);
		QObject::connect(toolsFrame, &ToolsFrame::OnUndoButtonReleasedSignal, this, &GameplayWidget::OnUndoButtonReleased);
		QObject::connect(toolsFrame, &ToolsFrame::OnFillButtonReleasedSignal, this, &GameplayWidget::OnFillButtonReleased);
		QObject::connect(toolsFrame, &ToolsFrame::OnCanvasClearedSignal, this, &GameplayWidget::OnCanvasCleared);
		QObject::connect(toolsFrame, &ToolsFrame::OnPencilButtonReleasedSignal, this, &GameplayWidget::OnPencilButtonReleased);

		backgroundForDrawer->setGeometry(0, 0, drawingBoard->width(), drawingBoard->height()); 
		backgroundForGuesser->setGeometry(0, 0, drawingBoard->width(), drawingBoard->height());

		firstShow = false;
	}

	AddPlayers();

	auto response = cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchplayers" },
		cpr::Parameters{
			{"password", UserCredentials::GetPassword()},
			{"username", UserCredentials::GetUsername()}
		}
	);
	auto playersResponse = crow::json::load(response.text);
	for (int index = 0; index < playersResponse["players"].size(); index++) {
		if (std::string(playersResponse["players"][index]["name"]) == UserCredentials::GetUsername()) {
			if (std::stoi(std::string(playersResponse["drawer index"])) == index) {
				m_isDrawer = true;
			}
			else {
				m_isDrawer = false;
			}
			break;
		}
	}
	backgroundForDrawer->setStyleSheet(
		"background-image: url(:/settings/WordsBackground);"
		"background-position: center;"
		"background-repeat: no-repeat;"
	);
	if (m_isDrawer) {
		ShowDrawerInterface();
	}
	else {
		ShowGuesserInterface();
	}
	chat->SetChatConfigurationAccordingToPlayerType(m_isDrawer);

	stop.store(false);

	std::thread checkForLobbyUpdates(&GameplayWidget::CheckForUpdatesInGameScene, this, std::ref(stop));
	checkForLobbyUpdates.detach();
}
