#pragma once

#include <QTableWidget>
#include <unordered_map>

class ScoreboardTable  : public QTableWidget
{
	Q_OBJECT

public:
	ScoreboardTable(QWidget *parent = nullptr);
	~ScoreboardTable();

	void AddPlayersToScoreboard(std::vector <std::tuple<QIcon, QString, QColor>> takenAvatars);
	void AddPointsToPlayerWithIndex(uint8_t index);

	void ClearScoreboard();
private:
	QFont nameFont																			 {};
	QFont pointsFont																		 {};
	QFont yourNameFont																		 {};
	//std::vector <std::tuple<QIcon, QString, QColor, int>> players							 {};
	std::vector <std::pair<QTableWidgetItem*, QTableWidgetItem*>> players					 {};
};
