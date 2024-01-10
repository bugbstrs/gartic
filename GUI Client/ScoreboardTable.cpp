#include "ScoreboardTable.h"
#include <random>
#include <crow.h>
#include "UserCredentials.h"

ScoreboardTable::ScoreboardTable(QWidget *parent)
	: QTableWidget{ parent },
	stop(false)
{
	nameFont.setFamily("Consolas");
	nameFont.setPixelSize(12);

	pointsFont.setFamily("Consolas");
	pointsFont.setPixelSize(20);

	yourNameFont.setFamily("Consolas");
	yourNameFont.setPixelSize(16);
	yourNameFont.setBold(true);
}

ScoreboardTable::~ScoreboardTable()
{}

void ScoreboardTable::AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor, QIcon>> takenAvatarsFromLobby)
{
	takenAvatars = takenAvatarsFromLobby;
	for (auto& avatar : takenAvatars) {
		QTableWidgetItem* name = new QTableWidgetItem(std::get<0>(avatar), std::get<1>(avatar));
		QTableWidgetItem* score = new QTableWidgetItem(QIcon(), QString::number(0));

		name->setBackground(std::get<2>(avatar));
		if (std::get<1>(avatar) == QString::fromUtf8(UserCredentials::GetUsername()))
			name->setFont(yourNameFont);
		else
			name->setFont(nameFont);
		name->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

		score->setBackground(std::get<2>(avatar));
		score->setFont(pointsFont);
		score->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

		int rowPosition = rowCount();
		insertRow(rowPosition);
		setItem(rowPosition, 0, name);
		setItem(rowPosition, 1, score);
		
		players.push_back({name, score});
	}
}

void ScoreboardTable::AddPointsToPlayerWithIndex(uint8_t index)
{
	players[0].second->setText(QString::number(players[0].second->text().toInt() + 10));
}

void ScoreboardTable::StopCheckingForPlayers(bool checkForPlayers)
{
	stop.store(true);
}

void ScoreboardTable::ClearScoreboard()
{
	players.clear();
	clearContents();
}

void ScoreboardTable::showEvent(QShowEvent* event)
{
	if (firstShow) {

		firstShow = false;
	}

	stop.store(false);

	std::thread checkForScoreboardUpdates(&ScoreboardTable::CheckForScoreboardUpdates, this, std::ref(stop));
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
			
			if (playersResponse["players"].size() != takenAvatars.size()) {
				int indexToRemove = -1;
				for (int index = 0; index < playersResponse["players"].size(); index++) {
					if (std::string(playersResponse["players"][index]["name"]) != std::get<1>(takenAvatars[index]).toUtf8().constData()) {
						indexToRemove = index;
						break;
					}
				}
				if (indexToRemove == -1) {
					indexToRemove = takenAvatars.size() - 1;
				}
				takenAvatars.erase(takenAvatars.begin() + indexToRemove);
				removeRow(indexToRemove);
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

