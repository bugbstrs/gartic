#include "GameplayWidget.h"
#include <qthread.h>
#include <QPropertyAnimation>
#include "UserCredentials.h"

GameplayWidget::GameplayWidget(QWidget* parent)
	: QWidget{ parent },
	m_stop(false)
{}

GameplayWidget::~GameplayWidget()
{}

void GameplayWidget::ChangePenColor(QColor color) noexcept
{
	if (m_isEraserEnabled) {
		m_drawingBoard->setCursor(m_pencilCursor);
		m_isEraserEnabled = false;
	}
	m_drawingBoard->ChangePenColor(color);
}

void GameplayWidget::ChangePenWidth(int width) noexcept
{
	m_drawingBoard->ChangePenWidth(width);
}

void GameplayWidget::SetGameSettings(std::tuple<int, int, int> gameSettings) noexcept
{
	m_drawTime = std::get<0>(gameSettings);
	m_rounds = std::get<1>(gameSettings);
	m_wordsCount = std::get<2>(gameSettings);
}

void GameplayWidget::StopCheckingForUpdates()
{
	m_chat->StopLookingForUpdates();
	m_drawingBoard->StopLookingForUpdates();
	m_stop.store(!m_stop.load());
}

void GameplayWidget::Clear() noexcept
{
	m_isEraserEnabled = false;
	m_wordToDraw->clear();
	m_scoreboardTable->ClearScoreboard();
	m_drawingBoard->setCursor(m_pencilCursor);
	m_drawingBoard->ResetBoard();
	m_toolsFrame->ResetCurrentColorView();
}

void GameplayWidget::OnCanvasCleared() noexcept
{
	m_drawingBoard->ClearCanvas();
}

void GameplayWidget::OnPencilButtonReleased() noexcept
{
	m_isEraserEnabled = false;
	m_drawingBoard->setCursor(m_pencilCursor);
	m_drawingBoard->ToggleEraser(false);
	m_drawingBoard->ToggleFill(false);
	m_drawingBoard->EnablePencil();
}

void GameplayWidget::OnEraserButtonReleased() noexcept
{
	m_isEraserEnabled = true;
	m_drawingBoard->setCursor(m_eraserCursor);
	m_drawingBoard->ToggleEraser(true);
	m_drawingBoard->ToggleFill(false);
}

void GameplayWidget::OnUndoButtonReleased() noexcept
{
	m_drawingBoard->UndoLastPath();
}

void GameplayWidget::OnFillButtonReleased() noexcept
{
	m_isEraserEnabled = false;
	m_drawingBoard->setCursor(m_fillCursor);
	m_drawingBoard->ToggleEraser(false);
	m_drawingBoard->ToggleFill(true);
}

void GameplayWidget::ShowDrawerInterface()
{
	QMetaObject::invokeMethod(this, [this]() {
		if (!m_backgroundForGuesser->isHidden())
			m_backgroundForGuesser->hide();
		m_scoreboardTable->ResetGuessedIcons();
		m_drawingBoard->SetupForDrawer(true);
		m_drawingBoard->setDisabled(false);
		m_toolsFrame->show();
		m_drawingBoard->ResetBoard();
		m_backgroundForDrawer->show();
		m_drawingBoard->SetIsChoosingWord(true);
		m_chat->ToggleAccessToWritingMessages(false);
		bool responseAccepted = false;
		while (!responseAccepted) {
			cpr::Response response = cpr::Get(
				cpr::Url{ "http://localhost:18080/fetchwordstoguess" },
				cpr::Parameters{
					{"password", UserCredentials::GetPassword()},
					{"username", UserCredentials::GetUsername()}
				}
			);
			if (response.status_code == 200) {
				auto words = crow::json::load(response.text);
				for (int index = 0; index < words["words"].size(); index++) {
					AddWordOption(std::string(words["words"][index]));
				}
				responseAccepted = true;
			}
		}
	}, Qt::QueuedConnection);
}

void GameplayWidget::ShowGuesserInterface()
{
	QMetaObject::invokeMethod(this, [this]() {
		if (!m_backgroundForDrawer->isHidden())
			m_backgroundForDrawer->hide();
		if (!m_wordsToChoose.empty()) {
			for (QPushButton* button : m_wordsToChoose) {
				delete button;
			}
			m_wordsToChoose.clear();
		}
		m_drawingBoard->ClearCanvas();
		m_backgroundForGuesser->show();
		m_waitingTextLabel->show();
		m_waitingTextLabel->raise();
		m_scoreboardTable->ResetGuessedIcons();
		m_chat->ToggleAccessToWritingMessages(true);
		m_toolsFrame->hide();
		m_drawingBoard->SetIsChoosingWord(true);
		m_drawingBoard->SetupForDrawer(false);
	}, Qt::QueuedConnection);
}

void GameplayWidget::BackgroundChangeForGuessersOnDrawerPickingWord()
{
	QMetaObject::invokeMethod(this, [this]() {
		m_drawingBoard->SetIsChoosingWord(false);
		m_drawingBoard->setDisabled(true);
		m_backgroundForGuesser->hide();
	}, Qt::QueuedConnection);
}

void GameplayWidget::BackgroundChangeForDrawer()
{
	QMetaObject::invokeMethod(this, [this]() {
		for (QPushButton* button : m_wordsToChoose) {
			delete button;
		}
		m_scoreboardTable->ResetGuessedIcons();
		m_wordsToChoose.clear();
		m_backgroundForDrawer->hide();
		m_drawingBoard->SetIsChoosingWord(false);
	}, Qt::QueuedConnection);
}

void GameplayWidget::CheckTime(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto fetchedTime = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchtime" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		if (fetchedTime.status_code == 200) {
			auto timeText = crow::json::load(fetchedTime.text);
			if (timeText.has("time"));
			m_timerLabel->setText(QString::fromUtf8(std::string(timeText["time"])));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	if (stop.load()) {

	}
}

void GameplayWidget::CheckForUpdatesInGameScene(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto fetchedPlayers = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchplayers" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		if (fetchedPlayers.status_code == 200) {
			auto playersResponse = crow::json::load(fetchedPlayers.text);
			if (playersResponse.has("players")) {
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
				for (int index = 0; index < playersResponse["players"].size(); index++) {
					if (std::string(playersResponse["players"][index]["guessed"]) == "true") {
						m_scoreboardTable->MarkGuessedForPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])));
					}
					m_scoreboardTable->SetPointsToPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])), std::stoi(std::string(playersResponse["players"][index]["points"])));
				}
			}
		}

		auto fetchedGameStatus = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchgamestatus" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		if (fetchedGameStatus.status_code == 200) {
			auto gameStatusText = crow::json::load(fetchedGameStatus.text);
			if (std::string(gameStatusText["status"]) == kDrawing) {
				if (!m_isDrawer && !m_backgroundForGuesser->isHidden()) {
					BackgroundChangeForGuessersOnDrawerPickingWord();
				}
				if (m_isDrawer && !m_backgroundForDrawer->isHidden()) {
					BackgroundChangeForDrawer();
				}
				auto randomWordPicked = cpr::Get(
					cpr::Url{ "http://localhost:18080/fetchwordtodisplay" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()}
					}
				);
				if (randomWordPicked.status_code == 200) {
					auto pickedWord = crow::json::load(randomWordPicked.text);
					if (pickedWord.has("word"))
						m_wordToDraw->setText(QString::fromUtf8(std::string(pickedWord["word"])));
				}
			}
			if (std::string(gameStatusText["status"]) == kPickingWord) {
				auto fetchedPlayers = cpr::Get(
					cpr::Url{ "http://localhost:18080/fetchplayers" },
					cpr::Parameters{
						{"password", UserCredentials::GetPassword()},
						{"username", UserCredentials::GetUsername()}
					}
				);
				if (fetchedPlayers.status_code == 200) {
					auto playersResponse = crow::json::load(fetchedPlayers.text);
					if (playersResponse.has("players")) {
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
					}
					m_wordToDraw->clear();
					if (m_isDrawer && m_backgroundForDrawer->isHidden())
						ShowDrawerInterface();
					if (!m_isDrawer && m_backgroundForGuesser->isHidden())
						ShowGuesserInterface();
				}
			}
			if (std::string(gameStatusText["status"]) == kFinished) {
				auto finalPlayersFetch = cpr::Get(
					cpr::Url{ "http://localhost:18080/fetchplayers" },
					cpr::Parameters{
						{"password", UserCredentials::GetPassword()},
						{"username", UserCredentials::GetUsername()}
					}
				);
				if (finalPlayersFetch.status_code == 200) {
					auto playersResponse = crow::json::load(finalPlayersFetch.text);
					m_drawingBoard->ClearCanvas();
					m_scoreboardTable->ClearScoreboard();
					for (int index = 0; index < playersResponse["players"].size(); index++) {
						m_scoreboardTable->SetPointsToPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])), std::stoi(std::string(playersResponse["players"][index]["points"])));
					}
				}
				stop.store(true);
				m_chat->StopLookingForUpdates();
				m_drawingBoard->StopLookingForUpdates();
				m_scoreboardTable->StopCheckingForPlayers();
				m_isDrawer = false;
				emit(OnGameFinished());
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(700));
	}
	if (stop.load()) {

	}
}

void GameplayWidget::CheckForLessNecessaryUpdates(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto fetchedRoundNumber = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchroundnumber" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		if (fetchedRoundNumber.status_code == 200) {
			auto roundText = crow::json::load(fetchedRoundNumber.text);
			if (roundText.has("round"))
				m_roundsLabel->setText(QString("Round %1").arg(QString::fromUtf8(std::string(roundText["round"]))));
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
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
		"    padding: 0px 0px;"
		"    font-family: \"Consolas\";"
		"    font-size: 12px;"
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
	m_wordsToChoose.push_back(wordButton);
	m_wordsToChooseLayout->addWidget(wordButton);
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

	if (m_firstShow) {
		m_wordToDraw = findChild<QLabel*>("wordToGuessLabel");
		m_timerLabel = findChild<QLabel*>("timerLabel");
		m_roundsLabel = findChild<QLabel*>("roundsLabel");
		m_drawingBoard = findChild<DrawingBoard*>("drawingBoardCanvas");
		m_toolsFrame = findChild<ToolsFrame*>("toolsFrame");
		m_chat = findChild<Chat*>("chatFrame");
		m_scoreboardTable = findChild<ScoreboardTable*>("scoreboardTable");
		m_backgroundForDrawer = new QWidget(m_drawingBoard);
		m_backgroundForGuesser = new QWidget(m_drawingBoard);
		m_wordsToChooseLayout = new QHBoxLayout(m_backgroundForDrawer);
		m_waitingForWordToBepickedLayout = new QHBoxLayout(m_backgroundForGuesser);

		m_waitingTextLabel->setStyleSheet("QLabel {"
			"  text-align: center;"
			"  font-size: 24px;"
			"  font-family: Consolas, monospace;"
			"}");
		m_waitingTextLabel->setText(QString("Waiting for ") + QString(m_scoreboardTable->itemAt(0, 0)->text()) + QString(" to choose a word..."));
		m_drawingBoard->SetIsChoosingWord(true);
		m_backgroundForGuesser->setStyleSheet(
			"background-color: grey;"
		);
		m_waitingForWordToBepickedLayout->addWidget(m_waitingTextLabel);
		m_waitingTextLabel->raise();
		m_waitingForWordToBepickedLayout->setAlignment(Qt::AlignCenter);
		m_backgroundForGuesser->setLayout(m_waitingForWordToBepickedLayout);

		QObject::connect(m_toolsFrame, &ToolsFrame::OnColorChangedSignal, this, &GameplayWidget::ChangePenColor);
		QObject::connect(m_toolsFrame, &ToolsFrame::OnWidthChangedSignal, this, &GameplayWidget::ChangePenWidth);
		QObject::connect(m_toolsFrame, &ToolsFrame::OnEraserButtonReleasedSignal, this, &GameplayWidget::OnEraserButtonReleased);
		QObject::connect(m_toolsFrame, &ToolsFrame::OnUndoButtonReleasedSignal, this, &GameplayWidget::OnUndoButtonReleased);
		QObject::connect(m_toolsFrame, &ToolsFrame::OnFillButtonReleasedSignal, this, &GameplayWidget::OnFillButtonReleased);
		QObject::connect(m_toolsFrame, &ToolsFrame::OnCanvasClearedSignal, this, &GameplayWidget::OnCanvasCleared);
		QObject::connect(m_toolsFrame, &ToolsFrame::OnPencilButtonReleasedSignal, this, &GameplayWidget::OnPencilButtonReleased);

		m_backgroundForDrawer->setGeometry(0, 0, m_drawingBoard->width(), m_drawingBoard->height());
		m_backgroundForGuesser->setGeometry(0, 0, m_drawingBoard->width(), m_drawingBoard->height());

		m_firstShow = false;
	}

	bool fetchedPlayersCorrectly = false;
	while (!fetchedPlayersCorrectly) {
		auto fetchedPlayers = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchplayers" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		if (fetchedPlayers.status_code == 200) {
			auto playersResponse = crow::json::load(fetchedPlayers.text);
			if (playersResponse.has("players")) {
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
			}
			fetchedPlayersCorrectly = true;
		}
	}
	m_backgroundForDrawer->setStyleSheet(
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

	m_stop.store(false);

	std::thread checkForLobbyUpdates(&GameplayWidget::CheckForUpdatesInGameScene, this, std::ref(m_stop));
	std::thread checkFurLessNecessaryUpdates(&GameplayWidget::CheckForLessNecessaryUpdates, this, std::ref(m_stop));
	std::thread checkTime(&GameplayWidget::CheckTime, this, std::ref(m_stop));

	checkForLobbyUpdates.detach();
	checkFurLessNecessaryUpdates.detach();
	checkTime.detach();
}
