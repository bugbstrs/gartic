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
	m_chat->StopCheckingForUpdates();
	m_drawingBoard->StopLookingForUpdates();
	m_stop.store(!m_stop.load());
}

void GameplayWidget::ResetGameStatus()
{
	m_gameStatus = kPickingWord;
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
		m_drawingBoard->setDisabled(false);
		if (!m_backgroundForDrawer->isHidden()) {
			m_backgroundForDrawer->hide();
			if (!m_wordsToChoose.empty()) {
				for (QPushButton* button : m_wordsToChoose) {
					delete button;
				}
				m_wordsToChoose.clear();
			}
		}
		m_drawingBoard->ClearAction();
		m_drawingBoard->SetupForDrawer(false);
		m_drawingBoard->SetIsChoosingWord(true);
		m_backgroundForGuesser->show();
		m_waitingTextLabel->raise();
		m_scoreboardTable->ResetGuessedIcons();
		m_chat->ToggleAccessToWritingMessages(true);
		m_toolsFrame->ResetCurrentColorView();
		m_toolsFrame->hide();
	}, Qt::QueuedConnection);
}

void GameplayWidget::HideBackgroundForGuesserWhenDrawingStarts()
{
	QMetaObject::invokeMethod(this, [this]() {
		m_drawingBoard->SetIsChoosingWord(false);
		m_drawingBoard->setDisabled(true);
		m_backgroundForGuesser->hide();
	}, Qt::QueuedConnection);
}

void GameplayWidget::HideBackgroundForDrawerWhenDrawingStarts()
{
	QMetaObject::invokeMethod(this, [this]() {
		for (QPushButton* button : m_wordsToChoose) {
			delete button;
		}
		m_drawingBoard->SetIsChoosingWord(false);
		m_scoreboardTable->ResetGuessedIcons();
		m_wordsToChoose.clear();
		m_backgroundForDrawer->hide();
	}, Qt::QueuedConnection);
}

void GameplayWidget::GetCurrentPlayers()
{
	QMetaObject::invokeMethod(this, [this]() {
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
		}
	}, Qt::DirectConnection);
}

void GameplayWidget::NotifyEndGame(bool leavedGame)
{
	m_stop.store(true);
	m_isDrawer = false;
	m_chat->StopCheckingForUpdates();
	m_drawingBoard->StopLookingForUpdates();
	m_drawingBoard->ClearAction();
	m_scoreboardTable->StopCheckingForPlayers(leavedGame);
}

void GameplayWidget::PickingWordActions()
{
	auto fetchedPlayers = cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchplayers" },
		cpr::Parameters{
			{"password", UserCredentials::GetPassword()},
			{"username", UserCredentials::GetUsername()}
		}
	);
	if (fetchedPlayers.status_code == 200) {
		auto playersResponse = crow::json::load(fetchedPlayers.text);
		for (int index = 0; index < playersResponse["players"].size(); index++) {
			if (std::string(playersResponse["players"][index]["name"]) == UserCredentials::GetUsername()) {
				if (std::stoi(std::string(playersResponse["drawer index"])) == index) {
					m_isDrawer = true;
				}
				else {
					m_isDrawer = false;
				}
			}
			if (std::stoi(std::string(playersResponse["drawer index"])) == index &&
				m_drawerName != QString::fromUtf8(std::string(playersResponse["players"][index]["name"])))
			{
				m_drawerName = QString::fromUtf8(std::string(playersResponse["players"][index]["name"]));
				QMetaObject::invokeMethod(m_waitingTextLabel, "setText", Qt::QueuedConnection,
					Q_ARG(QString, QString("Waiting for ") + m_drawerName + QString(" to choose a word...")));
			}
		}
		m_wordToDraw->clear();
		if (m_isDrawer && m_backgroundForDrawer->isHidden())
			ShowDrawerInterface();
		if (!m_isDrawer && m_backgroundForGuesser->isHidden())
			ShowGuesserInterface();
	}
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
			QMetaObject::invokeMethod(m_timerLabel, "setText", Qt::DirectConnection,
				Q_ARG(QString, QString::fromUtf8(std::string(crow::json::load(fetchedTime.text)["time"]))));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
	}
	if (stop.load()) {

	}
}

void GameplayWidget::CheckForGameStatus()
{
	auto fetchedGameStatus = cpr::Get(
		cpr::Url{ "http://localhost:18080/fetchgamestatus" },
		cpr::Parameters{
			{"username", UserCredentials::GetUsername()},
			{"password", UserCredentials::GetPassword()}
		}
	);
	if (fetchedGameStatus.status_code == 200) {
		auto gameStatusText = crow::json::load(fetchedGameStatus.text);
		if (std::string(gameStatusText["status"]) == kPickingWord) {
			m_gameStatus = kPickingWord;
		}
		else if (std::string(gameStatusText["status"]) == kDrawing) {
			m_gameStatus = kDrawing;
		}
		else if (std::string(gameStatusText["status"]) == kFinished) {
			m_gameStatus = kFinished;
		}
	}
}

void GameplayWidget::CheckForUpdatesInGameScene(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		CheckForGameStatus();
		GetCurrentPlayers();
		if (m_gameStatus == kPickingWord) {
			PickingWordActions();
		}
		else if (m_gameStatus == kDrawing) {
			if (!m_isDrawer && !m_backgroundForGuesser->isHidden()) {
				HideBackgroundForGuesserWhenDrawingStarts();
			}
			if (m_isDrawer && !m_backgroundForDrawer->isHidden()) {
				HideBackgroundForDrawerWhenDrawingStarts();
			}
			auto randomWordPicked = cpr::Get(
				cpr::Url{ "http://localhost:18080/fetchwordtodisplay" },
				cpr::Parameters{
					{"username", UserCredentials::GetUsername()},
					{"password", UserCredentials::GetPassword()}
				}
			);
			if (randomWordPicked.status_code == 200) {
				QMetaObject::invokeMethod(m_wordToDraw, "setText", Qt::QueuedConnection,
					Q_ARG(QString, QString::fromUtf8(std::string(crow::json::load(randomWordPicked.text)["word"]))));
			}
		}
		else if (m_gameStatus == kFinished) {
			NotifyEndGame(false);
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
			QMetaObject::invokeMethod(m_roundsLabel, "setText", Qt::QueuedConnection,
				Q_ARG(QString, QString("Round %1").arg(QString::fromUtf8(std::string(crow::json::load(fetchedRoundNumber.text)["round"])))));
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
	QObject::connect(wordButton, &QPushButton::released, [wordButton]() {
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

		m_backgroundForDrawer->setStyleSheet(
			"background-image: url(:/settings/WordsBackground);"
			"background-position: center;"
			"background-repeat: no-repeat;"
		);
		m_waitingTextLabel->setStyleSheet("QLabel {"
			"  text-align: center;"
			"  font-size: 24px;"
			"  font-family: Consolas, monospace;"
			"}");
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

	m_gameStatus = kPickingWord;

	m_chat->Clear();

	m_drawerName = m_scoreboardTable->itemAt(0, 0)->text();
	m_waitingTextLabel->setText(QString("Waiting for ") + m_drawerName + QString(" to choose a word..."));

	m_drawingBoard->SetIsChoosingWord(true);

	if (!m_wordsToChoose.empty()) {
		for (QPushButton* button : m_wordsToChoose) {
			delete button;
		}
		m_wordsToChoose.clear();
	}

	m_stop.store(false);

	std::thread checkTime(&GameplayWidget::CheckTime, this, std::ref(m_stop));
	std::thread checkForLobbyUpdates(&GameplayWidget::CheckForUpdatesInGameScene, this, std::ref(m_stop));
	std::thread checkFurLessNecessaryUpdates(&GameplayWidget::CheckForLessNecessaryUpdates, this, std::ref(m_stop));

	checkTime.detach();
	checkFurLessNecessaryUpdates.detach();
	checkForLobbyUpdates.detach();
}
