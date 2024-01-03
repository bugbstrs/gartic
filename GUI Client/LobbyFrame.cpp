#include "LobbyFrame.h"
#include "UserCredentials.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <crow.h>

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

		if (!m_isLeader) {
			startGameButton->hide();
		}

		QObject::connect(startGameButton, &QPushButton::released, this, [this]() {
			stop.store(true);
		});

		stop.store(false);

		std::thread checkForNewPlayers(&LobbyFrame::CheckForNewPlayersJoined, this, std::ref(stop));
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

void LobbyFrame::CheckForNewPlayersJoined(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto users = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchusers" },
			cpr::Parameters{
				{"username", UserCredentials::GerUsername()},
				{"password", UserCredentials::GetPassword()}
			}
		);
		auto usersVector = crow::json::load(users.text);
		int a = lobbyTable->GetPlayersNumber();
		if (usersVector.size() != lobbyTable->GetPlayersNumber()) {
			for (int index = a; index < usersVector.size(); index++)
				lobbyTable->AddPlayer(std::string(usersVector[index]["username"]));
		}
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}
