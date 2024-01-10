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

	void StopCheckingForPlayers(bool checkForPlayers);
	void ClearScoreboard();
	void CheckForScoreboardUpdates(std::atomic<bool>& stop);
	void showEvent(QShowEvent* event) override;

private:

private:
	std::atomic<bool> stop;
	bool firstShow{ true };
	int currentIndex = 0;
	QFont nameFont																			 {};
	QFont pointsFont																		 {};
	QFont yourNameFont																		 {};
	std::vector <std::pair<QTableWidgetItem*, QTableWidgetItem*>> players					 {};
	std::vector<std::tuple<QIcon, QString, QColor, QIcon>> takenAvatars;
};
