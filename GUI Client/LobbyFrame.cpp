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
		codeLineEdit = findChild<QLineEdit*>("codeLineEdit");
		lobbyTable = findChild<LobbyTable*>("lobbyTable");

		if (m_isLeader) {
			QObject::connect(startGameButton, &QPushButton::released, this, [this]() {
				//Muta aici din mainwindow crearea de game
				auto createGame = cpr::Post(
					cpr::Url{ "http://localhost:18080/creategame" },
					cpr::Parameters{
						{"username", UserCredentials::GetUsername()},
						{"password", UserCredentials::GetPassword()}
					}
				);
			});
			QObject::connect(roundsComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
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
			});
			QObject::connect(wordCountComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
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
			});
			QObject::connect(drawTimeComboBox, &QComboBox::currentTextChanged, this, [this](const QString& newText) {
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
			});
		}
		else {
			startGameButton->hide();
		}

		stop.store(false);

		std::thread checkForNewPlayers(&LobbyFrame::CheckForLobbyUpdates, this, std::ref(stop));
		checkForNewPlayers.detach();

		firstShow = false;
	}
}

void LobbyFrame::SetCode(QString codeText) noexcept
{
	codeLineEdit->setText(codeText);
}

void LobbyFrame::SetLeaderStatus(bool isLeader) noexcept
{
	m_isLeader = isLeader;
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
		auto usersVector = crow::json::load(users.text);
		int playersNumber = lobbyTable->GetPlayersNumber();
		if (usersVector["users"].size() != lobbyTable->GetPlayersNumber()) {
			for (int index = playersNumber; index < usersVector.size(); index++)
				lobbyTable->AddPlayer(std::string(usersVector["users"][index]));
		}

		if (!m_isLeader) {
			auto gameSettings = cpr::Get(
				cpr::Url{ "http://localhost:18080/fetchsettings" },
				cpr::Parameters{
					{"username", UserCredentials::GetUsername()},
					{"password", UserCredentials::GetPassword()}
				}
			);
			auto settings = crow::json::load(gameSettings.text);
			drawTimeComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["drawTime"])));
			roundsComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["roundsNumber"])));
			wordCountComboBox->setCurrentText(QString::fromUtf8(std::string(settings["settings"]["wordCount"])));
		}

		auto gameState = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchlobbystatus" },
			cpr::Parameters{
				{"username", UserCredentials::GetUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		auto state = crow::json::load(gameState.text);
		if (std::string(state["status"]) == kStartedGame) {
			stop.store(true);
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	if (stop.load()) {
		emit OnGameStarted();
	}
}
