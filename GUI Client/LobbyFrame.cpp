#include "LobbyFrame.h"
#include "UserCredentials.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <crow.h>
#include <iostream>

LobbyFrame::LobbyFrame(QWidget *parent)
	: QFrame(parent),
	m_stop(false)
{}

LobbyFrame::~LobbyFrame()
{}

std::tuple<int, int, int> LobbyFrame::GetGameSettings()
{
	return { m_drawTimeComboBox->currentText().toInt(), m_roundsComboBox->currentText().toInt(), m_wordCountComboBox->currentText().toInt() };
}

void LobbyFrame::showEvent(QShowEvent * event)
{
	if (m_firstShow) {
		m_drawTimeComboBox = findChild<QComboBox*>("drawTimeComboBox");
		m_roundsComboBox = findChild<QComboBox*>("roundsComboBox");
		m_wordCountComboBox = findChild<QComboBox*>("wordCountComboBox");
		m_startGameButton = findChild<QPushButton*>("startGameButton");
		m_leaveLobbyButton = findChild<QPushButton*>("exitLobbyButton");
		m_codeLineEdit = findChild<QLineEdit*>("codeLineEdit");
		m_lobbyTable = findChild<LobbyTable*>("lobbyTable");
		
		QObject::connect(m_startGameButton, &QPushButton::released, this, [this]() {
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

		QObject::connect(m_roundsComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
			bool accepted = false;

			while (!accepted)
			{
				auto modifySettings = cpr::Post(
					cpr::Url{ "http://localhost:18080/setsettings" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()},
						{"roundsnumber", newText.toUtf8().constData()},
						{"wordcount", m_wordCountComboBox->currentText().toUtf8().constData()},
						{"drawtime", m_drawTimeComboBox->currentText().toUtf8().constData()}
					}
				);

				if (modifySettings.status_code == 200)
				{
					accepted = true;
				}
			}
		});
		
		QObject::connect(m_wordCountComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
			bool accepted = false;

			while (!accepted)
			{
				auto modifySettings = cpr::Post(
					cpr::Url{ "http://localhost:18080/setsettings" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()},
						{"roundsnumber", m_roundsComboBox->currentText().toUtf8().constData()},
						{"wordcount", newText.toUtf8().constData()},
						{"drawtime",  m_drawTimeComboBox->currentText().toUtf8().constData()}
					}
				);

				if (modifySettings.status_code == 200)
				{
					accepted = true;
				}
			}
		});

		QObject::connect(m_drawTimeComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
			bool accepted = false;

			while (!accepted)
			{
				auto modifySettings = cpr::Post(
					cpr::Url{ "http://localhost:18080/setsettings" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()},
						{"roundsnumber", m_roundsComboBox->currentText().toUtf8().constData()},
						{"wordcount", m_wordCountComboBox->currentText().toUtf8().constData()},
						{"drawtime", newText.toUtf8().constData()}
					}
				);

				if (modifySettings.status_code == 200)
				{
					accepted = true;
				}
			}
		});

		QObject::connect(m_leaveLobbyButton, &QPushButton::released, this, [this]() {
			m_leaveGame = true;
			m_stop.store(true);
		});

		m_firstShow = false;
	}
	m_stop.store(false);

	if (m_isLeader) {
		SetLeaderSettings();
	}
	else {
		SetNonLeaderSettings();
	}

	std::thread checkForLobbyUpdates(&LobbyFrame::CheckForLobbyUpdates, this, std::ref(m_stop));
	checkForLobbyUpdates.detach();
}

void LobbyFrame::SetCode(QString codeText) noexcept
{
	m_codeLineEdit->setText(codeText);
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
			int playersNumber = m_lobbyTable->GetPlayersNumber();
			if (usersVector["users"].size() != m_lobbyTable->GetPlayersNumber()) {
				if (usersVector["users"].size() > m_lobbyTable->GetPlayersNumber()) {
					for (int index = playersNumber; index < usersVector["users"].size(); index++)
                        m_lobbyTable->AddPlayer(std::string(usersVector["users"][index]));
				}
				else {
                    m_lobbyTable->ClearLobby();
					for (int index = 0; index < usersVector["users"].size(); index++)
                        m_lobbyTable->AddPlayer(std::string(usersVector["users"][index]));
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
				m_drawTimeComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["drawTime"])));
				m_roundsComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["roundsNumber"])));
				m_wordCountComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["wordCount"])));
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
		if (m_leaveGame)
			emit OnLobbyLeft();
		else
			emit OnGameStarted();
	}
}

void LobbyFrame::SetLeaderSettings()
{
	QMetaObject::invokeMethod(this, [this]() {
		m_startGameButton->show();
		m_drawTimeComboBox->setDisabled(false);
		m_roundsComboBox->setDisabled(false);
		m_wordCountComboBox->setDisabled(false);
	}, Qt::QueuedConnection);
}

void LobbyFrame::SetNonLeaderSettings()
{
	QMetaObject::invokeMethod(this, [this]() {
		m_startGameButton->hide();
		m_drawTimeComboBox->setDisabled(true);
		m_roundsComboBox->setDisabled(true);
		m_wordCountComboBox->setDisabled(true);
	}, Qt::QueuedConnection);
}

