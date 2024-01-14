#include "LobbyFrame.h"
#include "UserCredentials.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <crow.h>
#include <iostream>

LobbyFrame::LobbyFrame(QWidget *parent)
	: QFrame(parent),
	stop(false)
{}

LobbyFrame::~LobbyFrame()
{}

std::tuple<int, int, int> LobbyFrame::GetGameSettings()
{
	return { drawTimeComboBox->currentText().toInt(), roundsComboBox->currentText().toInt(), wordCountComboBox->currentText().toInt() };
}

void LobbyFrame::showEvent(QShowEvent * event)
{
	if (firstShow) {
		drawTimeComboBox = findChild<QComboBox*>("drawTimeComboBox");
		roundsComboBox = findChild<QComboBox*>("roundsComboBox");
		wordCountComboBox = findChild<QComboBox*>("wordCountComboBox");
		startGameButton = findChild<QPushButton*>("startGameButton");
		leaveLobbyButton = findChild<QPushButton*>("exitLobbyButton");
		codeLineEdit = findChild<QLineEdit*>("codeLineEdit");
		lobbyTable = findChild<LobbyTable*>("lobbyTable");
		
		QObject::connect(startGameButton, &QPushButton::released, this, [this]() {
			bool accepted = false;
			
			while (!accepted)
			{
				auto createGame = cpr::Post(
					cpr::Url{ "http://localhost:18080/creategame" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()}
					}
				);

				if (createGame.status_code == 200)
				{
					accepted = true;
				}
			}
		});

		QObject::connect(roundsComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
			bool accepted = false;

			while (!accepted)
			{
				auto modifySettings = cpr::Post(
					cpr::Url{ "http://localhost:18080/setsettings" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()},
						{"roundsnumber", newText.toUtf8().constData()},
						{"wordcount", wordCountComboBox->currentText().toUtf8().constData()},
						{"drawtime", drawTimeComboBox->currentText().toUtf8().constData()}
					}
				);

				if (modifySettings.status_code == 200)
				{
					accepted = true;
				}
			}
		});
		
		QObject::connect(wordCountComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
			bool accepted = false;

			while (!accepted)
			{
				auto modifySettings = cpr::Post(
					cpr::Url{ "http://localhost:18080/setsettings" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()},
						{"roundsnumber", roundsComboBox->currentText().toUtf8().constData()},
						{"wordcount", newText.toUtf8().constData()},
						{"drawtime",  drawTimeComboBox->currentText().toUtf8().constData()}
					}
				);

				if (modifySettings.status_code == 200)
				{
					accepted = true;
				}
			}
		});

		QObject::connect(drawTimeComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
			bool accepted = false;

			while (!accepted)
			{
				auto modifySettings = cpr::Post(
					cpr::Url{ "http://localhost:18080/setsettings" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()},
						{"roundsnumber", roundsComboBox->currentText().toUtf8().constData()},
						{"wordcount", wordCountComboBox->currentText().toUtf8().constData()},
						{"drawtime", newText.toUtf8().constData()}
					}
				);

				if (modifySettings.status_code == 200)
				{
					accepted = true;
				}
			}
		});

		QObject::connect(leaveLobbyButton, &QPushButton::released, this, [this]() {
			leaveGame = true;
			stop.store(true);
		});

		firstShow = false;
	}
	stop.store(false);

	if (m_isLeader) {
		SetLeaderSettings();
	}
	else {
		SetNonLeaderSettings();
	}

	std::thread checkForLobbyUpdates(&LobbyFrame::CheckForLobbyUpdates, this, std::ref(stop));
	checkForLobbyUpdates.detach();
}

void LobbyFrame::SetCode(QString codeText) noexcept
{
	codeLineEdit->setText(codeText);
}

void LobbyFrame::SetLeaderStatus(bool isLeader) noexcept
{
	m_isLeader = isLeader;
}

void LobbyFrame::Clear()
{
	m_isLeader = false;
	bool leaveGame{ false };
}

void LobbyFrame::CheckForLobbyUpdates(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto users = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchusers" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		if (users.status_code == 200) {
			auto usersVector = crow::json::load(users.text);
			int playersNumber = lobbyTable->GetPlayersNumber();
			if (usersVector["users"].size() != lobbyTable->GetPlayersNumber()) {
				if (usersVector["users"].size() > lobbyTable->GetPlayersNumber()) {
					for (int index = playersNumber; index < usersVector["users"].size(); index++)
						lobbyTable->AddPlayer(std::string(usersVector["users"][index]));
				}
				else {
					lobbyTable->ClearLobby();
					for (int index = 0; index < usersVector["users"].size(); index++)
						lobbyTable->AddPlayer(std::string(usersVector["users"][index]));
					if (usersVector["users"][0] == UserCredentials::GetUsername() && !m_isLeader) {
						m_isLeader = true;
						SetLeaderSettings();
					}
				}
			}
		}

		if (!m_isLeader) {
			auto gameSettings = cpr::Get(
				cpr::Url{ "http://localhost:18080/fetchsettings" },
				cpr::Parameters{
					{"username", UserCredentials::GetUsername()},
					{"password", UserCredentials::GetPassword()}
				}
			);
			if (gameSettings.status_code == 200) {
				auto settings = crow::json::load(gameSettings.text);
				drawTimeComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["drawTime"])));
				roundsComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["roundsNumber"])));
				wordCountComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["wordCount"])));
			}
		}

		auto gameState = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchlobbystatus" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		if (gameState.status_code == 200) {
			auto state = crow::json::load(gameState.text);
			if (std::string(state["status"]) == kStartedGame) {
				stop.store(true);
			}
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	if (stop.load()) {
		if (leaveGame)
			emit OnLobbyLeft();
		else
			emit OnGameStarted();
	}
}

void LobbyFrame::SetLeaderSettings()
{
	QMetaObject::invokeMethod(this, [this]() {
		startGameButton->show();
		drawTimeComboBox->setDisabled(false);
		roundsComboBox->setDisabled(false);
		wordCountComboBox->setDisabled(false);
	}, Qt::QueuedConnection);
}

void LobbyFrame::SetNonLeaderSettings()
{
	QMetaObject::invokeMethod(this, [this]() {
		startGameButton->hide();
		drawTimeComboBox->setDisabled(true);
		roundsComboBox->setDisabled(true);
		wordCountComboBox->setDisabled(true);
	}, Qt::QueuedConnection);
}

