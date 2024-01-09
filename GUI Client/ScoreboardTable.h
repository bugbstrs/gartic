#pragma once

#include <QTableWidget>
#include <unordered_map>

class ScoreboardTable  : public QTableWidget
{
	Q_OBJECT

public:
	ScoreboardTable(QWidget *parent = nullptr);
	~ScoreboardTable();

	void AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor, QIcon>> takenAvatarsFromLobby);
	void AddPointsToPlayerWithIndex(uint8_t index);

	void ClearScoreboard();
private:
	int currentIndex = 0;
	QFont nameFont																			 {};
	QFont pointsFont																		 {};
	QFont yourNameFont																		 {};
	std::vector <std::pair<QTableWidgetItem*, QTableWidgetItem*>> players					 {};
	std::vector<std::tuple<QIcon, QString, QColor, QIcon>> takenAvatars;
};
