#include "ScoreboardTable.h"
#include <random>
#include <crow.h>
#include "UserCredentials.h"

ScoreboardTable::ScoreboardTable(QWidget* parent)
	: QTableWidget{ parent },
	m_stop(false),
	m_drawerIcon(QIcon(":/image/pencil"))
{
	m_nameFont.setFamily("Consolas");
	m_nameFont.setPixelSize(12);

	m_pointsFont.setFamily("Consolas");
	m_pointsFont.setPixelSize(20);

	m_yourNameFont.setFamily("Consolas");
	m_yourNameFont.setPixelSize(16);
	m_yourNameFont.setBold(true);
}

ScoreboardTable::~ScoreboardTable()
{}

void ScoreboardTable::AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor, QIcon>> takenAvatarsFromLobby) noexcept
{
	clearContents();
	setRowCount(0);
	m_takenAvatars = takenAvatarsFromLobby;
	for (auto& avatar : m_takenAvatars) {
		QTableWidgetItem* name = new QTableWidgetItem(std::get<0>(avatar), std::get<1>(avatar));
		QTableWidgetItem* score = new QTableWidgetItem(QIcon(), QString::number(0));

		name->setBackground(std::get<2>(avatar));
		if (std::get<1>(avatar) == QString::fromUtf8(UserCredentials::GetUsername()))
			name->setFont(m_yourNameFont);
		else
			name->setFont(m_nameFont);
		name->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

		score->setBackground(std::get<2>(avatar));
		score->setFont(m_pointsFont);
		score->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

		int rowPosition = rowCount();
		insertRow(rowPosition);
		setItem(rowPosition, 0, name);
		setItem(rowPosition, 1, score);

		m_players.push_back({ name, score });
		m_playersToSendForResultsDisplaying.push_back({ name->icon(), name->text(), score->text().toInt(), std::get<2>(avatar) });
	}
}

void ScoreboardTable::SetPointsToPlayer(const QString& username, int numberOfPoints) noexcept
{
	QMetaObject::invokeMethod(this, [this, username, numberOfPoints]() {
		for (int index{ 0 }; index < m_players.size(); index++) {
			if (m_players[index].first->text() == username) {
				m_players[index].second->setText(QString::number(numberOfPoints));
				std::get<2>(m_playersToSendForResultsDisplaying[index]) = numberOfPoints;
				break;
			}
		}
	}, Qt::QueuedConnection);
}

void ScoreboardTable::MarkGuessedForPlayer(const QString& username) noexcept
{
	QMetaObject::invokeMethod(this, [this, username]() {
		for (int index{ 0 }; index < m_players.size(); index++) {
			if (m_players[index].first) {
				if (m_players[index].first->text() == username) {
					m_players[index].second->setIcon(std::get<3>(m_takenAvatars[index]));
					break;
				}
			}
		}
	}, Qt::QueuedConnection);
}

std::vector <std::tuple<QIcon, QString, int, QColor>> ScoreboardTable::GetPlayersOrdered() const noexcept
{
	return m_playersToSendForResultsDisplaying;
}

void ScoreboardTable::StopCheckingForPlayers(bool leavedGame)
{
	m_leavedGame = leavedGame;
	m_stop.store(true);
}

void ScoreboardTable::ResetGuessedIcons() noexcept
{
	for (int index{ 0 }; index < m_players.size(); index++) {
		if (!m_players[index].second->icon().isNull()) {
			m_players[index].second->setIcon(QIcon());
		}
	}
}

void ScoreboardTable::ClearScoreboard() noexcept
{
	QMetaObject::invokeMethod(this, [this]() {
		m_players.clear();
		m_playersToSendForResultsDisplaying.clear();
		m_takenAvatars.clear();
		clearContents();
	}, Qt::QueuedConnection);
}

void ScoreboardTable::showEvent(QShowEvent* event)
{
	if (m_firstShow) {

		m_firstShow = false;
	}

	m_stop.store(false);

	std::thread checkForScoreboardUpdates(&ScoreboardTable::CheckForScoreboardUpdates, this, std::ref(m_stop));
	checkForScoreboardUpdates.detach();
}

void ScoreboardTable::MarkDrawer(const QString& username)
{
	QMetaObject::invokeMethod(this, [this, username]() {
		for (int index{ 0 }; index < m_players.size(); index++) {
			if (m_players[index].first) {
				if (m_players[index].first->text() == username && m_players[index].second->icon().isNull()) {
					m_players[index].second->setIcon(m_drawerIcon);
					break;
				}
			}
		}
	}, Qt::QueuedConnection);
}

void ScoreboardTable::CheckForScoreboardUpdates(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto response = cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchplayers" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		if (response.status_code == 200)
		{
			auto playersResponse = crow::json::load(response.text);
			if (playersResponse["players"].size() != m_players.size()) {
				int indexToRemove = -1;
				for (int index{ 0 }; index < playersResponse["players"].size(); index++) {
					if (std::string(playersResponse["players"][index]["name"]) != std::get<1>(m_takenAvatars[index]).toUtf8().constData()) {
						indexToRemove = index;
						break;
					}
				}
				if (indexToRemove == -1) {
					indexToRemove = m_takenAvatars.size() - 1;
				}
				m_players.erase(m_players.begin() + indexToRemove);
				m_takenAvatars.erase(m_takenAvatars.begin() + indexToRemove);
				removeRow(indexToRemove);
			}
			else {
				for (int index{ 0 }; index < playersResponse["players"].size(); index++) {
					if (std::stoi(std::string(playersResponse["drawer index"])) == index) {
						MarkDrawer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])));
					}
					if (std::string(playersResponse["players"][index]["guessed"]) == "true") {
						MarkGuessedForPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])));
					}
					SetPointsToPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])), std::stoi(std::string(playersResponse["players"][index]["points"])));
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	if (stop.load()) {
		if (m_leavedGame) {
			m_leavedGame = false;
			return;
		}
		bool gotFinalScores = false;
		while (!gotFinalScores) {
			auto response = cpr::Get(
				cpr::Url{ "http://localhost:18080/fetchplayers" },
				cpr::Parameters{
					{"password", UserCredentials::GetPassword()},
					{"username", UserCredentials::GetUsername()}
				}
			);
			if (response.status_code == 200)
			{
				gotFinalScores = true;
				auto playersResponse = crow::json::load(response.text);
				for (int index{ 0 }; index < playersResponse["players"].size(); index++) {
					SetPointsToPlayer(QString::fromUtf8(std::string(playersResponse["players"][index]["name"])), std::stoi(std::string(playersResponse["players"][index]["points"])));
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		emit OnGameFinished();
	}
}

