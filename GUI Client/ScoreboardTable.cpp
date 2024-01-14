#include "ScoreboardTable.h"
#include <random>
#include <crow.h>
#include "UserCredentials.h"

ScoreboardTable::ScoreboardTable(QWidget *parent)
	: QTableWidget{ parent },
	m_stop(false)
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

void ScoreboardTable::AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor, QIcon>> takenAvatarsFromLobby)
{
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
		
		m_players.push_back({name, score});
		m_playersToSendForResultsDisplaying.push_back({ name->icon(), name->text(), score->text().toInt(), std::get<2>(avatar)});
	}
}

void ScoreboardTable::AddPointsToPlayerWithIndex(uint8_t index)
{
	m_players[0].second->setText(QString::number(m_players[0].second->text().toInt() + 10));
}

void ScoreboardTable::SetPointsToPlayer(const QString& username, int numberOfPoints)
{
	for (int index = 0; index < rowCount(); index++) {
		if (m_players[index].first->text() == username) {
			m_players[index].second->setText(QString::number(numberOfPoints));
			std::get<2>(m_playersToSendForResultsDisplaying[index]) = numberOfPoints;
			break;
		}
	}
}

void ScoreboardTable::MarkGuessedForPlayer(const QString& username)
{
	for (int index = 0; index < rowCount(); index++) {
		if (m_players[index].first->text() == username) {
			m_players[index].second->setIcon(std::get<3>(m_takenAvatars[index]));
			break;
		}
	}
}

std::vector <std::tuple<QIcon, QString, int, QColor>> ScoreboardTable::GetPlayersOrdered()
{
	return m_playersToSendForResultsDisplaying;
}

void ScoreboardTable::StopCheckingForPlayers()
{
	m_stop.store(true);
}

void ScoreboardTable::ResetGuessedIcons()
{
	for (int index = 0; index < rowCount(); index++) {
		m_players[index].second->setIcon(QIcon());
	}
}

void ScoreboardTable::ClearScoreboard()
{
	m_players.clear();
	clearContents();
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

void ScoreboardTable::CheckForScoreboardUpdates(std::atomic<bool>& stop)
{
	while (!stop.load()) {
		auto response =  cpr::Get(
			cpr::Url{ "http://localhost:18080/fetchplayers" },
			cpr::Parameters{
				{"password", UserCredentials::GetPassword()},
				{"username", UserCredentials::GetUsername()}
			}
		);
		if (response.status_code == 200)
		{
			auto playersResponse = crow::json::load(response.text);
			if (playersResponse.has("players")) {
				if (playersResponse["players"].size() != m_takenAvatars.size()) {
					int indexToRemove = -1;
					for (int index = 0; index < playersResponse["players"].size(); index++) {
						if (std::string(playersResponse["players"][index]["name"]) != std::get<1>(m_takenAvatars[index]).toUtf8().constData()) {
							indexToRemove = index;
							break;
						}
					}
					if (indexToRemove == -1) {
						indexToRemove = m_takenAvatars.size() - 1;
					}
					m_takenAvatars.erase(m_takenAvatars.begin() + indexToRemove);
					removeRow(indexToRemove);
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

